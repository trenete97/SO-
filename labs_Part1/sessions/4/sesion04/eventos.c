#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int segundos = 0;

void trata_alarma(int s)
{
    char buff[256];
    if(s == SIGALRM) {
        segundos++;
        sprintf(buff,"Segundos: %d\n",segundos);
        write(1, buff, strlen(buff));
    }
    else {
        segundos = 0;
    }

    alarm(1);
}
int main(int argc,char *argv[])
{
    signal (SIGALRM, trata_alarma);
    signal (SIGUSR1, trata_alarma);
    alarm(1);
    while(1){
        pause();
    }
}
