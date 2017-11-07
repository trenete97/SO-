#include <unistd.h>

#include "dbg.h"

void Usage()
{
	fprintf(stderr, "Correct usage:  mod51 number\n");
	exit(0);
}

int main(int argc, char *argv[])
{
	int i, n, num;

	if (argc!=2) Usage();

	n = atoi(argv[1]);
	srand(getpid());

	for (i=0; i<n; i++) {
		num = rand() % 10;
		if (write(1, &num, sizeof(num))< 0) panic("write");
	}
}
