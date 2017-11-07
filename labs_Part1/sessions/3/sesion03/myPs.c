#include <unistd.h>
#include <stdio.h>
#include <string.h>

void error_y_exit(char *msg,int exit_status) {
    perror(msg);
    exit(exit_status);
}

/* Ejecuta el comando ps -u username mediante la llamada al sistema execlp */
/* Devuelve: el código de error en el caso de que no se haya podido mutar */
void muta_a_PS(char *username) {
    execlp("ps", "-u", username, (char*)NULL);
    error_y_exit("Ha fallado la mutación al ps", 1);
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
                muta_a_PS(argv[1]);
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
