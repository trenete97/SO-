#include <unistd.h>
#include <stdio.h>
#include <string.h>

void error_y_exit(char *msg,int exit_status) {
    perror(msg);
    exit(exit_status);
}

int main(int argc,char *argv[])
{
    int pid;
    char buffer[80];
    if (argc > 1) {
        pid = fork();
        switch (pid) { /* Esta linea la ejecutan tanto el padre como el hijo */

            case 0: /* Escribe aqui el codigo del proceso hijo */
                sprintf(buffer,"HIJO: Soy el proceso %d %s \n",getpid(), argv[1]);
                write(1, buffer, strlen(buffer));
                break;

            case -1:/* Se ha producido un error */
                error_y_exit("Error en el fork", 1);
                break;

            default: /* (pid != 0) && (pid != -1) */
                /* Escribe aqui el codigo del padre */
                sprintf(buffer,"PADRE: Soy el proceso %d\n",getpid());
                write(1, buffer, strlen(buffer));
        }
        while(1);
    }
}
