#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

char buffer[80] = { 0 };

//  Llamadas al sistema encapsuladas para facilitar el control y reporte
//  de errores


void error(int line, char* msg) {
    char buff[128] = { 0 };
    sprintf(buff, "error en linea %d: %s", line, msg);
    perror(buff);
    exit(EXIT_FAILURE);
}

int my_write(int fd, void* c, int size, int line) {
    int ret = write(fd, c, size);
    if (ret < 0) error(line, "write");
    return ret;
}

void usage(int line) {


	sprintf(buffer,"usage: ./acertar_1 N\nN es un entero entre 0 y 9");
	error(line,buffer);
	exit(EXIT_FAILURE);
}
int main(int argc,char *argv[]) {
	int n;
	int f;
	

	if (argc != 2) usage(__LINE__);
	n = atoi(argv[1]);
	if ((n < 0)||(n>9)) usage(__LINE__);

	f = getpid()%10;

	//sprintf(buffer,"comparo %d con %d\n",n,f);
	//my_write(STDOUT_FILENO, buffer, strlen(buffer),__LINE__);

	if (n==f){ exit(1); 
	} else {
		exit(0);
	}
}
	

