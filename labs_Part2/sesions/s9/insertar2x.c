#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void Usage() {
	char buffer[256];
	sprintf(buffer, "Usage: insertar2x arg1 arg2 arg3\nEste programa escribe una X las posiciones arg2 y arg2+1 \n");
	write(1, buffer, strlen(buffer));
	exit(0);
}

main (int argc, char *argv[])
{	
	if(argc != 2) Usage();
	int pos1 = atoi(argv[1]);
	int fd = open("arxiu", O_RDWR);
	int tamany = lseek(fd, 0, SEEK_END);
	char buffer[tamany-pos1+1];
	char c = 'X';
	lseek(fd, pos1, SEEK_SET);
	read(fd, &buffer, tamany-pos1+1);
	lseek(fd, pos1, SEEK_SET);
	write(fd, &c, sizeof(char));
	write(fd, &buffer, strlen(buffer));
	close(fd);

}
