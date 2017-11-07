#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


main (int argc, char *argv[])
{
	
	char buffer[256];
	int ret = read(0, buffer, sizeof(buffer));
	int fd = open("pipe1", O_WRONLY);
	while(ret > 0) {
		write(fd, buffer, ret);
		ret = read(0, buffer, sizeof(buffer));
	}
	close(fd);

}
