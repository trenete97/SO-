#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main( int argc, char *argv[] )
{
	if (argc != 2) exit(0);
	if (strlen(argv[1]) != 1) exit(0);
	write(1,argv[1],1);
	pause();
	return(0);
}
