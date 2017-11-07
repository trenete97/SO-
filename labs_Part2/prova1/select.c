#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>




int main(int argc, char **argv) 
{
	int r; 
	int p[2];
	int c;
	int pid_h;
	char *lletres;
	char *lletra;

	lletres = argv[1];
	lletra = argv[2];
	if (pipe(p)<0) {perror("pipe ");exit(1);}

	pid_h = fork();
	if (pid_h<0) {perror("fork show");exit(1);}
	if (pid_h==0) { //show
		dup2(p[1],1);
		close(p[0]);
		close(p[1]);
		execlp("./show","./show",lletres,(char*)NULL);
		perror("exec show");	
		exit(1);

	}
	close(p[1]);
	pid_h = fork();
	if (pid_h<0) {perror("fork grep");exit(1);}
	if (pid_h==0){
		dup2(p[0],0);
		close(p[0]);
		close(1);
		c = open("mypipe", O_WRONLY);
		if (c<0) {perror("opening mypipe WR");exit(1);}
		execlp("grep", "grep",lletra,(char*)NULL);
		perror("exec grep");	
		exit(1);
	}
	close(p[0]);
	pid_h = fork();
	if (pid_h<0) {perror("fork tr");exit(1);}
	if (pid_h==0){
		close(0);
		c = open("mypipe", O_RDONLY);
		if (c<0) {perror("opening mypipe RD");exit(1);}
		execlp("tr", "tr",",","=",(char*)NULL);
		perror("exec tr");	
		exit(1);
	}
	while(waitpid(-1, NULL, 0) >0);
}
