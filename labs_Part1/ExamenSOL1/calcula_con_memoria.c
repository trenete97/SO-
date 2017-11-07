#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SYSCALL_ERROR 1

// Esta funcion no es relevante, solo pierde tiempo 
int calcula(unsigned int i)
{
	int it;
	int ret=0;
	srand(i);
	for (it=0;it<i;it++){
		ret=ret+rand();
	}
	return ret;
}			

void usage()
{
	char b[128];
	sprintf(b,"usage:calcula_con_memoria semilla ITERACIONES_MAIN (>0)\n");
	write(1,b,strlen(b));
	exit(EXIT_FAILURE);
}

void main(int argc,char *argv[])
{
	int i,ITERACIONES_MAIN=1,ITERACION_ACTUAL,semilla;
	char b[128];
	int *res;
	if (argc!=3) usage();
	semilla=atoi(argv[1]);
	ITERACIONES_MAIN=atoi(argv[2]);
	if (ITERACIONES_MAIN<0) usage();
	sprintf(b,"limite anterior heap %x\n",sbrk(0));
	write(1,b,strlen(b));
	res=malloc(ITERACIONES_MAIN*sizeof(int)); // reservamos espacio para N enteros
	sprintf(b,"limite posterior heap %x\n",sbrk(0));
	write(1,b,strlen(b));
	for (i=0;i<ITERACIONES_MAIN;i++){
		ITERACION_ACTUAL=i;
		res[i]=calcula((unsigned)semilla);
	}	
	sprintf(b,"resultado %d\n",res[0]); // Aqui en el enunciado no indicaba que habia que hacer, mostramos solo  1 elemento pero podriamos mostrar todos
	write(1,b,strlen(b));
	free(res); // liberamos el espacio reservado
}
