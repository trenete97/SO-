#include <stdio.h>
#include <unistd.h>

#include "dbg.h"

void Usage()
{
	fprintf(stderr, "Usage: arith N\nN ha de ser 1 o 2\n");
	exit(1);
}

int main(int argc, char *argv[])
{
	int n, num, ret;

	if (argc !=2) Usage();

	n = atoi(argv[1]);

	if ((n<1) || (n>2)) Usage();

	while ((ret=read(0, &num, sizeof(int)))>0) {
		if (ret < sizeof(int)) panic("partial read!!");

		if (n==1) num = num -1;
		else num = 1<<num;
	
		if (write(1, &num, sizeof(int)) < 0) panic("write");
	}

	if (ret<0) panic("read");
}
