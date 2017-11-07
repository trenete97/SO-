#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


extern end;
extern etext;
extern edata;

const int var_global_const = 1;
int var_global_sin_inicializar;
int var_global_inicializada = 9;

int main (int argc, char **argv)
{

  int variable_local;
  int *puntero_con_resultado_de_malloc;

  puntero_con_resultado_de_malloc = (int *) malloc (sizeof (int));

//  printf ("DATO: Tamano de pÃ¡gina de memoria: %d\n\n", getpagesize ());
  printf ("A continuacion se muestran las direcciones desordenadas de:\n\n");

  printf ("la funcion main\n");
  printf ("resultado_de_malloc\n");
//  printf ("edata, etext y end\n");
  printf ("var_global_sin_inicializar\n");
  printf ("var_global_inicializada\n");
  printf ("variable_local\n\n\n");
  // printf("%p    = &var_global_const\n",  &var_global_const);
  // printf("%p    = &argc\n",  &argc);

 // printf ("%p\n",  &etext);
  printf ("%p\n",  &var_global_sin_inicializar);
  //printf ("%p\n",  &end);
  printf ("%p\n",  puntero_con_resultado_de_malloc);
  printf ("%p\n",  main);
  printf ("%p\n",  &var_global_inicializada);
 // printf ("%p\n",  &edata);
  printf ("%p\n",  &variable_local);


  printf
    ("\n\nCopia los datos del problema y asocia a cada direccion su item\n\n");
  printf
    ("\n\nEl resultado de la asociacion tendra el formato:\n=================================\n08123456 resultado_de_malloc\n...\n08654321 la funcion main\n");
  printf ("\n\nPulsa una tecla para acabar el programa\n");

  getchar ();

return 1;
}
