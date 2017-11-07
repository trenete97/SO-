#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char **argv) 
{
	int r; 
	char lletra;
	int num;
	char buff[20];
	char *file;
	int f;

	file = argv[1];
	f = open(file, O_RDONLY);
	r = read(f, &lletra, sizeof(lletra));
	while(r>0) {
		write(1, &lletra, sizeof(lletra));
		if (lletra == ',') {
				r = read(f,&num, sizeof(num)); //llegim numero
				if (r>0) {
					sprintf(buff, "%d", num);
					write(1, buff, strlen(buff));
				} else {
					perror("reading number");
					exit(1);
				}
		}
		r = read(f, &lletra, sizeof(lletra));
	}

	return 0;
}
