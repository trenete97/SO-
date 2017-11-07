#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>



void usage()
{
	char b[128];
	sprintf(b,"connector pipe_AB pipe_BA fichero_out\n");
	write(1,b,strlen(b));
	exit(1);
}
void pipe_cerrada(int s)
{
	char buff[128];
	sprintf(buff,"Finalizamos pq nos han cerrado la pipe de escritura\n");
	write(1,buff,strlen(buff));
	exit(1);
}
void main(int argc,char*argv[])
{
	char buff[64];// leeemos con un buffer
	int ret;
	int pid;
	int pipe_AB,pipe_BA,fd;
	if (argc!=4) usage();
	pid=fork();
	if (pid==0){ // lee de entrada std y envia a la pipe_AB
		// Capturamos el signal
		signal(SIGPIPE,pipe_cerrada);
		// Abrimos la pipe de escritura
		pipe_AB=open(argv[1],O_WRONLY);
		if (pipe_AB<0){
			printf("abro %s\n",argv[1]);
			perror("Error abriendo pipe_AB");
			exit(1);
		}
		while((ret=read(0,buff,sizeof(buff)))>0){
			// Escribimos SOLO lo que leemos, usamos ret para escribir
			write(pipe_AB,buff,ret);
		}	
		exit(0);
	}else if (pid<0){
		perror("error en fork\n");
		exit(1);
	}else{// redirecciona input de pipe_BA y salida a nuevo fichero
		//STDIN
		pipe_BA=open(argv[2],O_RDONLY);
		if (pipe_BA<0){		
			printf("abro %s\n",argv[2]);
			perror("Error open pipe_BA");
			exit(1);
		}
		dup2(pipe_BA,0); // Duplicamos el canal de la pipe en la entrada std
		close(pipe_BA);  // Cerramos pipe_BA para evitar problemas de bloqueos
		//STDOUT
		close(1);
		// La semantica del open define que se utiliza el primer canal libre de la tabla
		fd=open(argv[3],O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR);
		if (fd<0){
			perror("Error open file");
			exit(1);
		}
		// El cat internamente implementa una lectura de la entrada std y escritura en la salida std
		execlp("cat","cat",NULL);
		perror("Error mutating\n");
		exit(1);
	}
}

	
