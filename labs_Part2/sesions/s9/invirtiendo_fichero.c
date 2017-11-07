#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void Usage() {
	char buffer[256];
	sprintf(buffer, "Usage: invirtiendo_fichero arg1 arg2\nEste programa escribe en un fichero arg2.inv el contenido invertido de arg2\n");
	write(1, buffer, strlen(buffer));
	exit(0);
}

main (int argc, char *argv[])
{	
	if(argc != 2) Usage();
	char arxiu[20]; 
	strcpy(arxiu, argv[1]);
	int fin = open(arxiu, O_RDONLY);
	if(fin < 0) perror("Error en el open");
	strcat(arxiu, ".inv");
	int fout = creat(arxiu, O_RDWR);
	if(fout < 0) perror("Error en create");

	char c;
	int new = lseek(fin, -1, SEEK_END);
	
	int r = read(fin, &c, sizeof(char));
	while(r > 0 && new >= 0) {
		write(fout, &c, r);
		new = lseek(fin, -2, SEEK_CUR);
		r = read(fin, &c, sizeof(char));
	}
	close(fin);
	close(fout);
}
