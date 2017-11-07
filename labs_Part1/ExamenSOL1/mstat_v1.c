#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


#define SYSCALL_ERROR 1
#define USER_ERROR 2

void usage(){
	char b[128];
	sprintf(b,"usage : mstat_v1 nom_fitxer1 [nom_fitxer2.. nom_fitxerN]\n");
	write(1,b,strlen(b));
	exit(EXIT_FAILURE);
}
void error_cs(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
void main(int argc,char *argv[])
{
	int ret,pid,ec,ret_wp;
	char b[128];
	int i;

	if (argc==1) usage();
	for (i=1;i<argc;i++){
		pid=fork();
		if (pid==0){
			sprintf(b,"Ejecutamos el comando stat del fichero %s\n",argv[i]);
			write(1,b,strlen(b));
			exit(EXIT_SUCCESS);
		}else if (pid<0){
			error_cs("Fallo en el fork ");
		}else{
			ret_wp=waitpid(-1,&ret,0);
			if (ret_wp<0) error_cs("fallo del waitpid, no deberia pasar");
		}
	}
}
