#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SYSCALL_ERROR 1
int ITERACION_ACTUAL;

// Esta funcion no es relevante, solo pierde tiempo 
void calcula(int i)
{
	int it;
	int fd;
	for (it=0;it<i;it++){
		fd=open("F",O_WRONLY|O_CREAT|O_TRUNC,S_IRWXU);
		if (fd<0){
			perror("Error en el open");
			exit(SYSCALL_ERROR);
		}
		write(fd,&it,sizeof(it));
		close(fd);
	}
}			
void usage(){
        char b[128];
        sprintf(b,"usage : calcula iteraciones_main(>0) iteraciones_calcula (>0) duracion_maxima(>0)\n");
        write(1,b,strlen(b));
        exit(EXIT_FAILURE);
}
void error_cs(char *msg)
{
        perror(msg);
        exit(EXIT_FAILURE);
}

void f_usr1(int s)
{
	char buffer[128];
	sprintf(buffer,"Valor de ITERACION_ACTUAL %d\n",ITERACION_ACTUAL);
	write(1,buffer,strlen(buffer));
}
void f_alarm(int s)
{
	char buffer[128];
	sprintf(buffer,"Valor de ITERACION_ACTUAL %d\n",ITERACION_ACTUAL);
	write(1,buffer,strlen(buffer));
	exit(1);
}
void main(int argc,char *argv[])
{
	int i,ITERACIONES_MAIN,ITERACIONES_CALCULA,duracion; 
	char b[128];
	if (argc!=4) usage();
	ITERACIONES_MAIN=atoi(argv[1]);
	ITERACIONES_CALCULA=atoi(argv[2]);
	duracion=atoi(argv[3]);
	if ((ITERACIONES_MAIN<0) || (ITERACIONES_CALCULA<0) || (duracion<0)) usage();
	signal(SIGUSR1,f_usr1);
	signal(SIGALRM,f_alarm);
	alarm(duracion);
	for (i=0;i<ITERACIONES_MAIN;i++){
		ITERACION_ACTUAL=i;
		calcula(ITERACIONES_CALCULA);
	}	
}
