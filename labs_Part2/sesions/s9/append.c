#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



main (int argc, char *argv[])
{	
	
	int fin = open("file.txt", O_RDWR);
	if(fin < 0) perror("Error en el open");
	
	char buffer[256];
	int r = read(fin, &buffer, sizeof(buffer));
	while(r > 0) {
		write(fin, &buffer, r);
		r = read(fin, &buffer, sizeof(buffer));
	}
	close(fin);
}
