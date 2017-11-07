#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

main (int argc, char *argv[]){
    int fd = open("salida.txt", O_RDWR);
    char buffer[2];
    char buffer2[2];
    lseek(fd, -1, SEEK_END);
    read(fd, &buffer, sizeof(char)); //llegim l'ultim element de tots i el guardem a buffer
    lseek(fd, -1, SEEK_CUR);
    sprintf(buffer2, "X"); //a buffer2 guardem x
    write (fd, buffer2, strlen (buffer2));
    write (fd, &buffer, sizeof(char));
    close(fd);
}
