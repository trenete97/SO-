#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

void error_y_exit(char *msg)
{
    perror(msg);
    exit(1);
}

void usage()
{
    char msg[256];

    sprintf(msg, "Usage: ansi filename n1 [n2..ni]\n");
    write(2, msg, strlen(msg));
    exit(1);
}

int main (int argc, char *argv[])
{
    int fd, n, nhijos, i, res, pid, size, leidos=0;
    char c;
    char buf[10];

    if (argc < 3) usage();

    nhijos = argc - 2;
    if ((fd = open (argv[1], O_RDWR)) < 0) error_y_exit("open");
    if ((size = lseek(fd, 0, SEEK_END)) < 0) error_y_exit("lseek");
    for (i = 0; i < nhijos; i++) {
        n = atoi(argv[i+2]);
        if (n != 1 && n != 2 && n != 4 && n != 7) usage();
	pid = fork();
	switch(pid) {
	    case 0:
		if (lseek(fd, 0, SEEK_SET) < 0) error_y_exit("lseek");
    		sprintf(buf,"\e[%sm",argv[i+2]);
    		if (write(1,&buf,strlen(buf)) < 0) error_y_exit("write");
    		while(leidos < size) {
		    if ((res = read(fd,&c,sizeof(c))) < 0) error_y_exit("read");
		    leidos += res;
        	    if (write(1,&c,res) < 0) error_y_exit("write");
    		}
    		sprintf(buf,"\e[0m\n");
    		if (write(1,&buf,strlen(buf)) < 0) error_y_exit("write");

		if (lseek(fd, 0, SEEK_END) < 0) error_y_exit("lseek");
		sprintf(buf,"(%s:%d)",argv[i+2],getpid());
		if (write(fd,&buf,strlen(buf)) < 0) error_y_exit("write");
		exit(0);

	    case 1: error_y_exit("fork"); 

	    default:
		if(waitpid(-1,NULL,0) < 0 ) error_y_exit("waitpid");
	}
    }   
    if(close (fd) < 0) error_y_exit("close fd");

    return 0;
}
