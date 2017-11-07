#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void Usage()
{
	char buff[128];
	sprintf(buff,"Usage: EscribeNumeros max filename\n");
	write(1,buff,strlen(buff));
	exit(1);
}
//EscribeNumeros max filename
void main(int argc,char *argv[])
{

	int i,max,fd;
	if (argc!=3) Usage();
	fd=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR);
	if (fd<0) {
		perror("Error open");
		exit(1);
	}
	max=atoi(argv[1]);
	for (i=0;i<max;i++){
		write(fd,&i,sizeof(int));
	}
	close(fd);	
}
