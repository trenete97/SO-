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
	sprintf(buff,"Usage: LeeNumeros filename\n");
	write(1,buff,strlen(buff));
	exit(1);
}
//EscribeNumeros max filename
void main(int argc,char *argv[])
{

	int i,max,fd;
	char buff[64];
	if (argc!=2) Usage();
	fd=open(argv[1],O_RDONLY);
	if (fd<0) {
		perror("Error open");
		exit(1);
	}
	while(read(fd,&i,sizeof(i))>0){
		sprintf(buff,"%d ",i);
		write(1,buff,strlen(buff));
	}
}
