#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void Usage()
{
	char buff[128];
	sprintf(buff,"Usage: pares filename\n");
	write(1,buff,strlen(buff));
	exit(1);
}
//pares filename
void main(int argc,char *argv[])
{

	int i,num,total=0,fd[2],pid;
	int num_procs=4;
	char partes[64],mi_parte[64];
	char buff[128];
	if (argc!=2) Usage();
	pipe(fd);
	sprintf(partes,"%d",num_procs);
	for (i=0;i<num_procs;i++){
		pid=fork();
		if (pid==0){
			dup2(fd[1],1);
			close(fd[0]);
			close(fd[1]);
			sprintf(mi_parte,"%d",i);
			execlp("./FiltraTrozo","FiltraTrozo",argv[1],partes,mi_parte,NULL);
			perror("Error al mutar");
			exit(1);
			
		}else if (pid<0){
			perror("error fork");
			exit(1);
		}
	}
	close(fd[1]);
	while(read(fd[0],&num,sizeof(int))>0){
		total=total+num;
	}
	while(waitpid(-1,NULL,0)>0);
	sprintf(buff,"Hat %d numeros pares\n",total);	
	write(1,buff,strlen(buff));
}
