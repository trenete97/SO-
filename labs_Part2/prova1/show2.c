#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char **argv) 
{
	int r,i; 
	char lletra;
	int num;
	char buff[20];
	char *file;
	int f;
	char buffer[(sizeof(int)+3*sizeof(char))*100];

	file = argv[1];
	f = open(file, O_RDONLY);
	r = read(f, buffer, sizeof(buffer));
	while(r>0) {
		i=0;
		while (i<r) {
			write(1, &buffer[i], sizeof(char));
			i+=sizeof(char);
			write(1, &buffer[i], sizeof(char));
			i+=sizeof(char);
			sprintf(buff,"%d", (int)buffer[i]);
			write(1,buff,strlen(buff));
			i+=sizeof(int);
			write(1, &buffer[i], sizeof(char));
			i+=sizeof(char);
		}	
		r = read(f, buffer, sizeof(buffer));
	}

	return 0;
}
