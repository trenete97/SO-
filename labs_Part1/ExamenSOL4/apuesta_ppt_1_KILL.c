#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
typedef void (*sighandler_t)(int);

char buffer[80] = { 0 };

//  Llamadas al sistema encapsuladas para facilitar el control y reporte
//  de errores

void f_USR2(int s){
}


void error(int line, char* msg) {
    char buff[128] = { 0 };
    sprintf(buff, "error en linea %d: %s", line, msg);
    perror(buff);
    exit(EXIT_FAILURE);
}

sighandler_t my_signal(int signum, sighandler_t handler, int line)
{
  sighandler_t ret = signal (signum, handler);
  if (ret == SIG_ERR)
    error (line, "signal");
  return ret;
}

int my_write(int fd, void* c, int size, int line) {
    int ret = write(fd, c, size);
    if (ret < 0) error(line, "write");
    return ret;
}

int my_kill(pid_t pid, int sig, int line){
    int ret = kill(pid, sig);
    if (ret == -1) error(line, "kill");
    return ret;
}

void usage(int line) {


	sprintf(buffer,"usage: ./apuesta_ppt_1\n");
	error(line,buffer);
	exit(EXIT_FAILURE);
}
int main(int argc,char *argv[]) {
	int f;
	

	if (argc != 1) usage(__LINE__);

	my_signal(SIGUSR2, f_USR2, __LINE__);

	srand(getppid()*getpid());
	f = rand()%4;

	sprintf(buffer,"res[%d]=%d\n",getpid(), f);
	my_write(STDOUT_FILENO, buffer, strlen(buffer),__LINE__);

	pause();

	if (f == 3){
		my_kill(getpid(), SIGKILL, __LINE__);
	}

	exit(f);
}
	

