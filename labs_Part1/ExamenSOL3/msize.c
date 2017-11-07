#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define CHUNK 4

int main()
{
	int i, lim0, lim1;
	char buff[128];

	for (i = 0; i < 2; i++) {
		lim0 = lim1 = (int) sbrk(0);
		while (lim0 == lim1) {
			malloc(CHUNK);
			lim1 = (int) sbrk(0);
		}
		sprintf(buff,"Limit inicial: [%x]\n", lim0);
		write(1,buff,strlen(buff));
		sprintf(buff,"Limit final  : [%x]\n", lim1);
		write(1,buff,strlen(buff));
		sprintf(buff,"Mida del bloc: [%d]\n", lim1-lim0);
		write(1,buff,strlen(buff));
	}
	return 0;
}
