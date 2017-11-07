#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int segundos = 0;
int sigant;

void trata_alarma(int s)
{
    char buff[256];
    if(s == SIGALRM) {
        segundos++;
        sprintf(buff,"Segundos: %d\n",segundos);
        write(1, buff, strlen(buff));
        if (s == sigant) signal (SIGALRM, SIG_DFL);
    }
    else {
        segundos = 0;
        if (s == sigant) signal (SIGUSR1, SIG_DFL);
    }

    alarm(1);
    sigant = s;
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
