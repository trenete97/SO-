#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

main (int argc, char *argv[]){
    int fd = creat("salida.txt", O_RDWR);
    char buffer[6];
    strcpy(buffer, "ABCD");
    write (fd, buffer, strlen (buffer));
    close(fd);
}
