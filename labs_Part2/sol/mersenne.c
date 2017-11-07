#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "dbg.h"

void Usage()
{
	fprintf(stderr, "Usage: mersenne file\n");
	exit(1);
}

#define NP "ff1"

int main(int argc, char *argv[])
{
	int n, num, ret, out, npread;
	int p1[2], p2[2], in;

	if (argc !=2) Usage();

	if (pipe(p1) < 0) panic("creant pipe");
	if (pipe(p2) < 0) panic("creant pipe");
	if (mkfifo(NP, 0660) < 0) 
		if (errno!=EEXIST) panic("creant NP");

	if ((in = open(argv[1], O_RDONLY)) < 0) panic("open");
	if ((out = open("salida", O_WRONLY|O_CREAT|O_EXCL, 0600)) < 0) 
		panic("open");

	switch(fork()){
		case -1: panic("fork");

		case 0: if (dup2(p1[0], 0) < 0) panic("dup2");
			if (close(1) < 0) panic("close");
			if (open(NP, O_WRONLY) != 1) panic("openNP");
			
			if (close(p1[0]) < 0) panic("close");
			if (close(p1[1]) < 0) panic("close");
			if (close(p2[0]) < 0) panic("close");
			if (close(p2[1]) < 0) panic("close");

			execlp("./arith", "arith", "2", NULL);
			panic("exec");
	}

	switch(fork()){
		case -1: panic("fork");

		case 0: if (dup2(p2[1], 1) < 0) panic("dup2");
			if (close(0) < 0) panic("close");
			if (open(NP, O_RDONLY) != 0) panic("openNP");
			
			if (close(p1[0]) < 0) panic("close");
			if (close(p1[1]) < 0) panic("close");
			if (close(p2[0]) < 0) panic("close");
			if (close(p2[1]) < 0) panic("close");

			execlp("./arith", "arith", "1", NULL);
			panic("exec");
	}

	while ((ret=read(in, &num, sizeof(int)))>0) {
		if (ret < sizeof(int)) panic("partial read!!");

		if (write(p1[1], &num, sizeof(int)) < 0) panic("write");
	}

	if (close(p1[0]) < 0) panic("close");
	if (close(p1[1]) < 0) panic("close");
	if (close(p2[1]) < 0) panic("close");

//	npread = open(NP, O_RDONLY);
//	if (npread<0) panic("open");

	while ((ret=read(p2[0], &num, sizeof(int)))>0) {
		if (ret < sizeof(int)) panic("partial read!!");

		if (write(out, &num, sizeof(int)) < 0) panic("write");
	}

	if (close(p2[0]) < 0) panic("close");

	if (ret<0) panic("read");
}
