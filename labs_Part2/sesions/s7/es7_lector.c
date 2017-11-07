#include <unistd.h>
//llegeix de maquina a enter
int main(){
	int num;
	char buff[256];
	read(0, &num, sizeof(int));
	sprintf(buff,"%d\n",num);
	write(1, buff, strlen(buff));
	
}
