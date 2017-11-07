#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


int pid;

//  Llamadas al sistema encapsuladas para facilitar el control y reporte
//  de errores

char buffer[128] = { 0 };

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

	sprintf(buffer, "Usage: ./acertar_N A B C ...J \nSe aceptan entre 1 y 10 argumentos, y cada uno es un entero entre 0 y 9\n\nSe obtiene un valor aleatorio para cada argumento y se devuelve el número de coincidencias.");
	error(line,buffer);
	exit(EXIT_FAILURE);
}


int main(int argc, char**argv)
{
	int i;

	if ((argc < 2 ) || (argc > 11)) { usage(__LINE__); }


	for (i= 1; i < argc ; i++) {
		pid = fork();
		switch (pid) {
			case -1: error(__LINE__,"fork\n");
			case 0: //fill
				 execlp( "./acertar_1", "acertar_1", argv[i], (char*)NULL );
				 error(__LINE__,"exec\n");
			default: //pare
				 {}
		}
	}	
	//wait a tots els fills
	
	int res=0;
	int np=0;
	int status;

	for (i= 1; i < argc ; i++) {
		int p = waitpid( -1, &status, 0 );
		if (p<0) {error(__LINE__,"waitpid\n");}

		if (WIFEXITED(status)) {
			np++;
                       res+=WEXITSTATUS(status);
		} 
	}
	sprintf(buffer, "PID=%d, Hijos acabados en exit=%d, num. aciertos=%d\n",getpid(), np, res);
	my_write(STDOUT_FILENO, buffer, strlen(buffer), __LINE__);

	return EXIT_SUCCESS;
}

