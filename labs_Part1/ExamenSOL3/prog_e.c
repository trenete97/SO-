#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

void error_cs(char *msj)
{
	perror(msj);
	exit(1);
}


int rebut = 0;

void Usage()
{
	char buff[64];
	sprintf(buff,"Usage: prog_* num\n");
	write(1,buff,strlen(buff));
	exit(1);

}

void funcio(int s)
{
	rebut = 1;
}

int main( int argc, char *argv[] )
{
	int i, num, fills[20], status;
	char buf[80] = "A";

	if (argc != 2) Usage();
	num = atoi( argv[1] );
	signal(SIGUSR1, funcio);
	for (i = 0; i < num; i++) {
		fills[i] = fork();
		if (fills[i] == 0) {
			execlp("./lletra", "lletra", buf, (char*) 0);
			error_cs("Error al execlp ");
		}else if (fills[i]<0) error_cs("Error al fork ");
		buf[0]++;
	}
	for (i = 0; i < num; i++) {
		rebut = 0;
		while(!rebut);
		kill(fills[i], SIGKILL);
	}
	for (i = 0; i < num; i++) {
		wait(&status);
	}
	write(1,"\n",1);
	return 0;
}
