#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>

main(int argc, char *argv[]) {
int fd,ret,i,valor;
char c;
char buf[128];

fd = open(argv[1], O_RDONLY);
if (fd < 0){
	if (errno == ENOENT) {
		perror("opening file");
		exit(1);
	}
}
ret = read (fd, &c, sizeof(char));
i=0;
while (ret > 0) {
	if (c != '\n'){
		buf[i] = c;
		i++;
	} else {
		buf[i] = '\0';
		valor=atoi(buf);
		write(1,&valor,sizeof(valor));
		i=0;
	}	
	ret = read(fd,&c,sizeof(char));	
}


}
