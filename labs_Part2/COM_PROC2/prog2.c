#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){
	int len, pd[2], fs, fd, nhijos, i, ret, num, cont=0;
	char buf[256];

	pipe(pd);

	nhijos = atoi(argv[1]);

	if ((fd = open("PH.dat", O_WRONLY|O_CREAT|O_TRUNC, 00640)) < 0){
		perror("Error en open salida");
		return -1;
	}

	for (i=0; i < nhijos; i++){
		ret = fork();

		if (ret == 0){//Hijo
			close(pd[1]);
			
			while(read(pd[0], &num, sizeof(int)) > 0){
				//sleep(1);
				write(fd, &num, sizeof(int));
				cont++;
			}
			len = sprintf(buf, "proceso %d leidos %d\n", getpid(), cont);
			write(1, buf, len);

			return 0;
		} else if(ret < 0){//Error
			perror("Error en fork");
			return -1;
		}
	}

	close(pd[0]);
	close(fd);

	if ((fs = open("num.dat", O_RDONLY)) < 0){
		perror("Error en open num");
		return -1;
	}

	ret = lseek(fs, 0, SEEK_END) / sizeof(int);

	for (i = ret-1; i >= 0; i--){
		lseek(fs, sizeof(int) * i, SEEK_SET);
		read(fs, &num, sizeof(int));
		write(pd[1], &num, sizeof(int));
	}
	close(pd[1]);

	while (waitpid(-1, NULL, 0) > 0);

	len = sprintf(buf, "Fin Padre\n");
	write(1, buf, len);

	return 0;
}
