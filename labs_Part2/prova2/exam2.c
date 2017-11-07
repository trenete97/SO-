#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

main(int argc, char *argv[]) {
int ret,petit,valor;
char c;
char buf[128];

ret = read (0, &petit, sizeof(int));
if (ret > 0) {
	ret = read (0, &valor, sizeof(int));
}
while (ret > 0) {
	if (valor < petit) {
		petit = valor;
	}
	ret = read (0, &valor, sizeof(int));
}
sprintf(buf,"%d\n",petit);
write (1, buf, strlen(buf));

}
