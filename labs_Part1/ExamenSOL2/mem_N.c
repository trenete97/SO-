#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void error(int line, char* msg) {
    char buff[128] = { 0 };
    sprintf(buff, "error en linea %d: %s", line, msg);
    perror(buff);
    exit(EXIT_FAILURE);
}

void *  my_malloc(int size, int line) {
    void * ret = malloc(size);
    if (ret == NULL ) error(line, "malloc");
    return ret;
}

int my_write(int fd, void* c, int size, int line) {
    int ret = write(fd, c, size);
    if (ret < 0) error(line, "write");
    return ret;
}


int main (int argc, char **argv)
{

void * heap_begin;
void * heap_end_malloc;
void * heap_end_free;

  int *puntero_con_resultado_de_malloc;

heap_begin=sbrk(0);
  puntero_con_resultado_de_malloc = (int *) my_malloc (atoi(argv[1]), __LINE__);
heap_end_malloc=sbrk(0);
  free(puntero_con_resultado_de_malloc);
heap_end_free=sbrk(0);

char buffer[128]={ 0 };
  sprintf (buffer, "begin=%p\nend_malloc=%p\nend_free=%p\nheap size_malloc:%ld\nheap size_free:%ld\n", heap_begin, heap_end_malloc, heap_end_free, heap_end_malloc-heap_begin,  heap_end_free-heap_begin);
  my_write (STDOUT_FILENO, buffer, strlen(buffer), __LINE__);

getchar();

return (EXIT_SUCCESS);
}
