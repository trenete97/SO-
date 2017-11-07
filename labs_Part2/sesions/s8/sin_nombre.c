#include <stdlib.h>
#include <string.h>

main (int argc, char *argv[])
{
	int fd[2];
	pipe(fd);
	int pid = fork();
	char buffer[256];
	switch(pid) {
		case 0: //proceso hijo
			close(0);
			dup(fd[0]);
			close(fd[0]);
			close(fd[1]);
			execlp("cat","cat",NULL);
			break;
		case -1:
			perror("Error en el fork");
			break;
		default: //proceso padre
			close(fd[0]);			
			sprintf(buffer, "Inicio\n");
			write(fd[1], buffer, strlen(buffer));
			close(fd[1]);
			waitpid(-1, NULL, 0);
			sprintf(buffer, "Fin\n");
			write(1, buffer, strlen(buffer));
			break;
	} 	
}
