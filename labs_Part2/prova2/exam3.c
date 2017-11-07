#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

main(int argc, char *argv[]) {
int pidh;
int fd[2];
char c;
char buf[128];

pipe(fd);
pidh=fork();
if (pidh == 0) {
	dup2(fd[1], 1);
	close(fd[1]); close(fd[0]);
	execlp("./exam1", "exam1",argv[1],(char *) 0);
}
close(fd[1]);
pidh=fork();
if (pidh == 0) {
	dup2(fd[0], 0);
	close(fd[0]);
	execlp("./exam2", "exam2",(char *) 0);
}
close(fd[0]);

while (waitpid(-1,NULL,0) > 0);
}
