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
	sprintf(buff,"Usage: FiltraTrozo filename num_parts part_to_read\n");
	write(1,buff,strlen(buff));
	exit(1);
}
//FiltraTrozo filename num_parts part_to_read
void main(int argc,char *argv[])
{

	int i,fd,partes,mi_parte;
	int size,total_size;
	int num_pars=0;
	char buff[64];
	if (argc!=4) Usage();
	fd=open(argv[1],O_RDONLY);
	if (fd<0) {
		perror("Error open");
		exit(1);
	}
	partes=atoi(argv[2]);
	mi_parte=atoi(argv[3]);
	total_size=lseek(fd,0,SEEK_END);	
	total_size=total_size/sizeof(int);
	size=total_size/partes;
	if (((total_size%partes)>0) && (mi_parte==(partes-1))) size=size+(total_size%partes);
	lseek(fd,mi_parte*(total_size/partes)*sizeof(int),SEEK_SET);
	while(size>0){
		read(fd,&i,sizeof(int));
		if ((i%2)==0) num_pars++;
		size--;
	}
	write(1,&num_pars,sizeof(int));
	sprintf(buff,"Hay %d pares\n",num_pars);
	write(2,buff,strlen(buff));
}
