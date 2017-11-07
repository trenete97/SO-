#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "socketMng.c"


main (int argc, char *argv[])
{
	char buffer[256];
	connectionFD = clientConnection (argv[1]);
  	if (connectionFD < 0)
    	{
     		 perror ("Error establishing connection\n");
      		exit (1);
    	}

 	int ret = read (connectionFD, buffer, sizeof (buffer));
  	while(ret > 0) {
  		write (1, buffer, ret);
		ret = read (connectionFD, buffer, sizeof (buffer));
	}
	closeConnection (connectionFD);
}
