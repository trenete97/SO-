#include <unistd.h>
#include <fcntl.h>

#include "dbg.h"

int main()
{
	int fd;

	fd = open("freq1a10.int", O_RDWR|O_TRUNC|O_CREAT, 0600);
	if (fd<0) panic("open");

	int zero = 0, counter;
	int i;

	for (i=0; i<10; i++) {
		if (write(fd, &zero, sizeof(zero)) < 0) panic("write");
	}


	int n, r;
	while ((r=read(0, &n, sizeof(n))) > 0) {
		if (r != sizeof(n)) panic("partial read");

		if ((n>=0) && (n<=9)) {
			if (lseek(fd, n*sizeof(zero), SEEK_SET) < 0)
				panic("lseek");

			if ((r=read(fd, &counter, sizeof(counter))) < 0)
				panic("read");
			if (r != sizeof(counter)) panic("partial read");

			counter++; 

			if (lseek(fd, -sizeof(zero), SEEK_CUR) < 0)
				panic("lseek");

			if (write(fd, &counter, sizeof(counter)) < 0)
				panic("read");
		}
	}
	if (r<0) panic("read");
}
