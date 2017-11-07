#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void error_y_exit(char *msg)
{
    perror(msg);
    exit(1);
}

void usage()
{
    char msg[256];

    sprintf(msg, "Usage: arith n, 0 < n < 4\n");
    write(2, msg, strlen(msg));
    exit(1);
}

int main(int argc, char *argv[])
{
        int n,value,ret;

        if (argc != 2)  usage();

        n = atoi(argv[1]);

	if (n < 1 || n > 3)  usage();

	while((ret=read(0,&value,sizeof(value))) > 0) {
	    switch(n) {
		case 1: value = value - 1;
			break;
		case 2: value = (int)pow(2,value);
			break;
		default: value = 3 * value;
	    }
	    if (write(1,&value,ret) < 0) 
		    error_y_exit("write");
        }
	if(ret < 0) error_y_exit("read");

	return 0;
}
