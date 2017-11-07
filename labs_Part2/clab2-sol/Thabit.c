#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

void error_y_exit(char *msg)
{
    perror(msg);
    exit(1);
}

void usage()
{
    char msg[256];

    sprintf(msg, "Usage: Thabit filename\n");
    write(2, msg, strlen(msg));
    exit(1);
}

int main(int argc,char *argv[])
{
    int i, pid, hijos, fdf1, fdf2, fdfin, fdfout, ret, value;
    int fdp1[2], fdp2[2];
    char buffer[80];

    if (argc != 2) usage();

    if((mknod("ff1", S_IFIFO|S_IRUSR|S_IWUSR, 0) < 0) && (errno != EEXIST))
        	error_y_exit("mknod");
    if((mknod("ff2", S_IFIFO|S_IRUSR|S_IWUSR, 0) < 0) && (errno != EEXIST))
                error_y_exit("mknod");

    pid = fork();
    switch (pid) {
      case 0: 
          if(pipe(fdp1) < 0) error_y_exit("pipe"); 
	  pid = fork();
          switch (pid) {
            case 0: 
	        if(pipe(fdp2) < 0) error_y_exit("pipe");
		pid = fork();
              	switch (pid) {
                  case 0:
	              if(dup2(fdp2[0],0) < 0) error_y_exit("dup2");
                      if(close(1) < 0) error_y_exit("close 1");
                      if(open("ff2", O_WRONLY) < 0) error_y_exit("open ff2");
		      if(close(fdp1[0]) < 0) error_y_exit("close fdp1[0]");
                      if(close(fdp1[1]) < 0) error_y_exit("close fdp1[1]");
                      if(close(fdp2[0]) < 0) error_y_exit("close fdp2[0]");
                      if(close(fdp2[1]) < 0) error_y_exit("close fdp2[1]");
                      if(execlp("./arith","arith","1",(char*)0) < 0) error_y_exit("execlp");
		  case -1: error_y_exit("fork");
                   
                  default:
		      if(dup2(fdp1[0],0) < 0) error_y_exit("dup2");
		      if(dup2(fdp2[1],1) < 0) error_y_exit("dup2");
    		      if(close(fdp1[0]) < 0) error_y_exit("close fdp1[0]");
                      if(close(fdp1[1]) < 0) error_y_exit("close fdp1[1]");
		      if(close(fdp2[0]) < 0) error_y_exit("close fdp2[0]");
                      if(close(fdp2[1]) < 0) error_y_exit("close fdp2[1]");
		      if(execlp("./arith","arith","3",(char*)0) < 0) error_y_exit("execlp");
		}
		case -1: error_y_exit("fork");

            	default: 
		    if(dup2(fdp1[1],1) < 0) error_y_exit("dup2");
                    if(close(0) < 0) error_y_exit("close 0");
                    if(open("ff1", O_RDONLY) < 0) error_y_exit("open ff1");
                    if(close(fdp1[0]) < 0) error_y_exit("close fdp1[0]");
                    if(close(fdp1[1]) < 0) error_y_exit("close fdp1[1]");
                    if(execlp("./arith","arith","2",(char*)0) < 0) error_y_exit("execlp");
 	  }

          case -1: error_y_exit("fork");

          default: 
              if((fdf1=open("ff1", O_WRONLY)) < 0) error_y_exit("open ff1");
	      if((fdfin=open(argv[1], O_RDONLY)) < 0) error_y_exit("open");

              while((ret=read(fdfin,&value,sizeof(value))) > 0) {
                  if (write(fdf1,&value,ret) < 0) error_y_exit("write");
              }
	      if(ret < 0) error_y_exit("read");
	      if(close(fdfin) < 0) error_y_exit("close fdfin");
	      if(close(fdf1) < 0) error_y_exit("close fdf1");

	      if((fdfout=open("salida", O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP)) < 0) error_y_exit("open");
	      if((fdf2=open("ff2", O_RDONLY)) < 0) error_y_exit("open ff2");
	      while((ret=read(fdf2,&value,sizeof(value))) > 0) {
	          sprintf(buffer, "%d ",value);
                  if(write(fdfout,buffer,strlen(buffer)) < 0) error_y_exit("write");
              }
              if(ret < 0) error_y_exit("read");
              if(close(fdfout) < 0) error_y_exit("close fdfout");
	      if(close(fdf2) < 0) error_y_exit("close fdf2");

    }
    return 0;
}
