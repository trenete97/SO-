
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void
error_y_exit (char *buff)
{
  perror (buff);
  exit (-1);
}

void
Usage (char *buff)
{
  printf (buff);
  exit (-1);
}

void
main (int argc, char *argv[])
{
  int leidos;
  char buffer[256];
  char print_buffer[256];

  int ps2grep[2];		// pipe del ps al grep
  int grep2wc[2];		// pipe del grep al wc
  int wc2father[2];		// pipe del wc al padre, para imprimir el mensaje de resultado


  if (argc != 2)
    Usage ("USAGE: ps_user username\n");

  pipe (ps2grep);
  pipe (grep2wc);
  pipe (wc2father);

  switch (fork ())		//proceso que ejecutará ps
    {
    case -1:
      error_y_exit ("FORK PS");
      break;
    case 0:
      dup2 (ps2grep[1], 1);	//redirección de la salida de ps hacia la pipe

      close (ps2grep[0]);	//Cierro todos los canales de pipe que no uso
      close (ps2grep[1]);
      close (grep2wc[0]);
      close (grep2wc[1]);
      close (wc2father[0]);
      close (wc2father[1]);

      execlp ("ps", "ps", "-eaf", (char *) NULL);	//mutación a ps
      error_y_exit ("MUTACION A PS");
      break;
    }


  switch (fork ())		//proceso que ejecutará grep
    {
    case -1:
      error_y_exit ("FORK GREP");
      break;
    case 0:
      dup2 (ps2grep[0], 0);	//redirección de la entrada de grep desde ps2grep
      dup2 (grep2wc[1], 1);	//redirección de la salida de grep hacia grep2ps

      close (ps2grep[0]);	//Cierro todos los canales de pipe que no uso
      close (ps2grep[1]);
      close (grep2wc[0]);
      close (grep2wc[1]);
      close (wc2father[0]);
      close (wc2father[1]);

      execlp ("grep", "grep", argv[1], (char *) NULL);	//mutación a grep
      error_y_exit ("MUTACION A GREP");
      break;
    }


  switch (fork ())		//proceso que ejecutará wc
    {
    case -1:
      error_y_exit ("FORK WC");
      break;
    case 0:
      dup2 (grep2wc[0], 0);	//redirección de la entrada de wc desde grep2wc
      dup2 (wc2father[1], 1);	//redirección de la salida de wc hacia wc2father

      close (ps2grep[0]);	//Cierro todos los canales de pipe que no uso
      close (ps2grep[1]);
      close (grep2wc[0]);
      close (grep2wc[1]);
      close (wc2father[0]);
      close (wc2father[1]);

      execlp ("wc", "wc", "-l", (char *) NULL);	//mutación a wc
      error_y_exit ("MUTACION A WC");
      break;
    }

//PADRE
  close (ps2grep[0]);		//Cierro todos los canales de pipe que no uso
  close (ps2grep[1]);
  close (grep2wc[0]);
  close (grep2wc[1]);
  close (wc2father[1]);
							//excepto el que me interesa para leer el resultado de wc

  while ((leidos = read (wc2father[0], buffer, 256)) > 0)
    {
      buffer[leidos - 1] = '\0';   //elimina el retorno de carro de wc
      sprintf (print_buffer, "El usuario %s está ejecutando %s procesos\n",
	       argv[1], buffer);
      write (1, print_buffer, strlen (print_buffer));
    }

  waitpid (-1, NULL, 0);
  waitpid (-1, NULL, 0);
  waitpid (-1, NULL, 0);

}
