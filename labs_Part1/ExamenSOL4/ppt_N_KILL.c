#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
typedef void (*sighandler_t)(int);


//pid de cada hijo
int pid[9];
//apuesta de cada hijo
int res[9] = { -1, -1, -1, -1, -1, -1, -1, -1, -1 };
//hijos acabados en exit
int np=0;
//numero de hijos finalizados
int num_sigchld=0;

//  Llamadas al sistema encapsuladas para facilitar el control y reporte
//  de errores

char buffer[128] = { 0 };

void error(int line, char* msg) {
    char buff[128] = { 0 };
    sprintf(buff, "error en linea %d: %s", line, msg);
    perror(buff);
    exit(EXIT_FAILURE);
}

sighandler_t
my_signal (int signum, sighandler_t handler, int line)
{
  sighandler_t ret = signal (signum, handler);
  if (ret == SIG_ERR)
    error (line, "signal");
  return ret;
}

int my_kill(pid_t pid, int sig, int line){
    int ret = kill(pid, sig);
    if (ret == -1) error(line, "kill");
    return ret;
}

int my_write(int fd, void* c, int size, int line) {
    int ret = write(fd, c, size);
    if (ret < 0) error(line, "write");
    return ret;
}

void f_sigchld(int s){
	if (s == SIGCHLD){
	
	int status,p;

	while (( p = waitpid( -1, &status, WNOHANG ))>0){
		if (p<0) {error(__LINE__,"waitpid\n");}

		if (WIFEXITED(status)) {
			np++;
                       res[num_sigchld]=WEXITSTATUS(status);
	sprintf(buffer, "Finalización normal de PID=%d, res[%d]=%d\n",getpid(), num_sigchld, res[num_sigchld]);
	my_write(STDOUT_FILENO, buffer, strlen(buffer), __LINE__);
		}  else if (WIFSIGNALED(status)) {
	sprintf(buffer, "Finalización por signal %d de PID=%d\n",WTERMSIG(status), getpid());
	my_write(STDOUT_FILENO, buffer, strlen(buffer), __LINE__);
                   }

		num_sigchld++;
	}
	}
}

void f_sigalrm(int s){
}

void usage(int line) {

	sprintf(buffer, "Usage: ./ppt_N n \nSe acepta 1 argumento, que es un entero entre 0 y 9\n\nSe obtienen n valores aleatorios (piedra, papel o tijera) y se devuelve el número de ganadores.");
	error(line,buffer);
	exit(EXIT_FAILURE);
}


int main(int argc, char**argv)
{
	int i,n;

	if (argc != 2 )  { usage(__LINE__); }
	n=atoi(argv[1]);
	if ((n < 0) || (n>9))  { usage(__LINE__); }

        my_signal (SIGCHLD, f_sigchld, __LINE__);

	for (i= 0; i < n ; i++) {
		pid[i] = fork();
		switch (pid[i]) {
			case -1: error(__LINE__,"fork\n");
			case 0: //fill
				 execlp( "./apuesta_ppt_1_KILL", "apuesta_ppt_1_KILL", (char*)NULL );
				 error(__LINE__,"exec\n");
			default: //pare
				 {}
		}
	}	

        my_signal (SIGALRM, f_sigalrm, __LINE__);

        alarm(1);
        pause();


	//SIGUSR2 a tots els fills
	for (i= 0; i < n ; i++) {
		my_kill(pid[i], SIGUSR2, __LINE__);
	}

	//wait a tots els fills

	while(num_sigchld<n);


	int ganadores=0;
	int soy_ganador;
	int j;

	for (i= 0; i < n ; i++) {
	if (res[i] != -1){
		soy_ganador=1;
		for (j= 0; j < n ; j++) {
		if (j != i){
			if (res[j] != -1){
			if (res[j] == ((res[i]+1)%3)){
				soy_ganador=0;
			}
			}
		}}
		if (soy_ganador == 1){
			ganadores++;
		}
	}}
	sprintf(buffer, "PID=%d, Hijos acabados en exit=%d, num. ganadores=%d\n",getpid(), np, ganadores);
	my_write(STDOUT_FILENO, buffer, strlen(buffer), __LINE__);

	return EXIT_SUCCESS;
}

