#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void usage(){
	char buffer[200];
	sprintf(buffer,"Usage:listaParametros arg1\n");
	write(1,buffer,strlen(buffer));
	sprintf(buffer,"Este programa escribe por su salida la lista de argumentos que recibe\n");
	write(1,buffer,strlen(buffer));
}


int main(int argc,char *argv[])
{
	int i;
	char buf[80];

	if(argc<2){ //si hay menos de 1 parametro
		usage();
	}else{
		for (i=0;i<argc;i++){
			if (i==0){
				sprintf(buf,"El argumento %d es %s (es el nombre del ejecutable)\n",i,argv[i]);
			}else{
				sprintf(buf,"El argumento %d es %s\n",i,argv[i]);
			}
			write(1,buf,strlen(buf));
		}
		
	}
	return 0;
}
