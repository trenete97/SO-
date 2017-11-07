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


void Usage()
{
	char buff[64];
	sprintf(buff,"Usage: prog_* num\n");
	write(1,buff,strlen(buff));
	exit(1);

}
void espera(int s)
{}
int main( int argc, char *argv[] )
{
	int i, num, fills[20], status;
	char buf[80] = "A";

	if (argc != 2) Usage();
	num = atoi( argv[1] );
	for (i = 0; i < num; i++) {
		fills[i] = fork();
		if (fills[i] == 0) {
			execlp("./lletra", "lletra", buf, (char*) 0);
			error_cs("Error al execlp ");
		}else if (fills[i]<0) error_cs("Error al fork ");
		buf[0]++;
	}
	signal(SIGALRM,espera);
	alarm(2);pause();
	for (i = 0; i < num; i++) {
		kill(fills[i], SIGKILL);
	}
	for (i = 0; i < num; i++) {
		wait(-1,&status,0);
	}
	write(1,"\n",1);
	return 0;
}
