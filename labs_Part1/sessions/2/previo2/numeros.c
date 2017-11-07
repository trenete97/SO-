#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/* función que compruebe que un string (en C se define como un “char *” o como un vector de caracteres, ya que no existe el tipo “string”) 1 que recibe como parámetro sólo contiene caracteres ASCII entre el ‘0’ y el ‘9’ (además del ‘\0’ al final y potencialmente el ‘-‘ al principio para los negativos). 
La función ha  de  comprobar  que  el  parámetro  puntero  no  sea  NULL.  La  función  devuelve  1  si  el string  representa  un  número  y  tiene  como  mucho 8 cifras (define  una  constante que llamaremos MAX_SIZE y utilízala), y 0 en cualquier otro caso.
*/
int esNumero(char *str) {
	int val = 1; int j;
	for (j = 0; j < strlen(str) && val == 1; j++) {
		if ((str[j] < '0' || str[j] > '9') && str[i] != '-') val = 0;
	}
	return val;
}

int main (int argc, char *argv[]) {
	char buf[50];
	int sol; int i;
	for (i = 1; i < argc; i++) {
		if (strlen(argv[i]) < 9 && argv[i] != NULL) {
			sol = esNumero((char *) argv[i]);
			sprintf(buf, "%d\n", sol);
			write(1, buf, strlen(buf));
		}
		else {
			sprintf(buf, "0\n");
			write(1, buf, strlen(buf));
		}
	}
}
