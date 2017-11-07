#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Usage()
{
	char buff[64];
	sprintf(buff,"Usage: prog_* num\n");
	write(1,buff,strlen(buff));
	exit(1);
}

int main( int argc, char *argv[] )
{
	int i, num;
	char buf[80];

	if (argc != 2) Usage();
	num = atoi( argv[1] );
	for (i = 0; i < num; i++) {
		sprintf(buf, "%c", 'A'+i);
		write(1, buf, 1);
	}
	write(1,"\n",1);
	return 0;
}
