#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



main (int argc, char *argv[])
{
	char buffer[256];
	int fd = open("pipe1", O_RDONLY);
	int ret = read(fd, buffer, sizeof(buffer));
	while(ret > 0) {
		write(1, buffer, ret);
		ret = read(fd, buffer, sizeof(buffer));
	}

	close(fd);
	
}
