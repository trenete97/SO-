#include <unistd.h>
#include <signal.h>
#include <string.h>

void trata_sigint(int s) {
	char buffer[256];
	strcpy(buffer, "\nRead con interrupt\n");
	write(1, &buffer, strlen(buffer));
}

main(){
	signal(SIGINT, trata_sigint);
	char c;
	char buffer[256];
	int r = read(0, &c, sizeof(char));
	if(r < 0) {	
		strcpy(buffer, "Read con error\n");
		write(1, &buffer, strlen(buffer));
	}
		
	else if(r > 0 && c != '\n') {	
		strcpy(buffer, "Read correcto:\n");
		write(1, &buffer, strlen(buffer));
		write(1, &c, sizeof(char));
		strcpy(buffer, "\n");
		write(1, &buffer, strlen(buffer));
	}
}
