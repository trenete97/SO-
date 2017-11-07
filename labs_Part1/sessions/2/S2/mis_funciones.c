
#include "mis_funciones.h"

int esNumero(char *str){

	char buffer[90];
	int neg=0;
	int r=1;
	int i=0;

	if(str!=NULL){ 
		if(*str=='-') str++; //si empeiza con el signo -
		if(*str=='\0') r=0;   //era solo el signo -
		for (i=1; *str!='\0' && r==1; ++i){
			if(i>MAX_SIZE) r=0;			//sprintf(buffer, "cadena > 8 \n");
			else if(*str<48 || *str>57)r=0;
			else str++;
			write(1, buffer, strlen(buffer)); 
		}
	}else sprintf(buffer, "puntero vacio \n");

	write(1, buffer, strlen(buffer)); 
	return r;

}

unsigned int char2int(char c){	
	return c-48; //ver tabla ascci
}

int mi_atoi(char *s){

	int neg, i, r=0;
	if(*s=='-'){ //si empeiza con el signo -
		s++;
		neg=1;
	}

	r+=char2int(*s); s++;
	while(*s!='\0'){
		r=r*10+char2int(*s);
		s++;
	}
	if(neg==1) r*=-1; //negativizar

	return r;
}


