#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 8

int esNumero(char *str){

	char buffer[90];
	int neg=0;
	int r=1;
	int i=0;

	if(str!=NULL){ 
		if(*str=='-') str++; //si empeiza con el signo -
		if(*str=='\0') r=0;   //era solo el signo -
		for (i=1; *str!='\0' && r==1; ++i){
			if(i>MAX_SIZE) r=0;	//sprintf(buffer, "cadena > 8 \n");
			else if(*str<48 || *str>57)r=0;
			else str++;
			write(1, buffer, strlen(buffer)); 
		}
	}else sprintf(buffer, "puntero vacio \n");

	write(1, buffer, strlen(buffer)); 
	return r;

}


int main(int argc,char *argv[]){
		

	char cadena[40];
	char buff[90];
	int i; 

	for (i = 1; i < argc && argv[i]!='\0'; i++){
		if((esNumero(argv[i]))==1){ sprintf(buff, "cadena correcta \n");}
		else{ sprintf(buff, "todo inapropiada \n"); }
		write(1, buff, strlen(buff)); 
	}

	
	return 0;
}
