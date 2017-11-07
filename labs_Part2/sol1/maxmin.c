#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

/* hola!!!! */

#include "dbg.h"

void Usage()
{
	fprintf(stderr, "Correct usage: maxmin num1 num2 ... numN\n");
	exit(0);
}

int main(int argc, char *argv[])
{
	int nfills, fd[2], i;

	nfills = argc-1;

	if (nfills == 0) Usage();

	if (pipe(fd) < 0) panic("pipe");

	for (i=0; i<nfills; i++) {
		switch(fork()) {
			case -1: panic("fork");

			case 0: if (dup2(fd[1], 1) < 0) panic("dup2");
				if (close(fd[0]) < 0) panic("close");
				if (close(fd[1]) < 0) panic("close");
				execl("./mod51", "mod51", argv[i+1], NULL);
				panic("exec");
		}
	}

	if (close(fd[1]) < 0) panic("close");

	switch(fork()) {
		case -1: panic("fork");

		case 0: if (dup2(fd[0], 0) < 0) panic("dup2");
			if (close(fd[0]) < 0) panic("close");
			execl("./filtra1a10", "filtra1a10", NULL);
			panic("exec");
	}

	for (i=0; i<(nfills+1); i++) {
		if (wait(NULL) < 0) panic("wait");
	}

	switch(fork()) {
		case -1: panic("fork");

		case 0: ;
			int fdf = open("freq1a10.int", O_RDONLY);
			if (fdf < 0) panic("open");
			int max_value = 0;
			int num, r;

			while ((r=read(fdf, &num, sizeof(num))) > 0) {
				if (num > max_value) {
					max_value = num;
				}
			}
			if (r<0) panic("read");
			char s[80];

			sprintf(s, "Maxim: %d\n", max_value);
			if (write(1, s, strlen(s)) < 0) panic("write");
			exit(0);

		default:
			if (wait(NULL) < 0) panic("wait");
	}

}
