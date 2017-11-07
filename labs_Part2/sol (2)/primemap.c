#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "dbg.h"

void
Usage ()
{
  fprintf (stderr, "Usage: primemap file\n");
  exit (1);
}

#define NP "ff1"

int
main (int argc, char *argv[])
{
  int n, num, ret, out, npread, i, st;
  int in;
  int mida, nprocs;
  char strout[80], strnum[80], c;

  if (argc != 2)
    Usage ();

  if ((in = open (argv[1], O_RDONLY)) < 0)
    panic ("open");

  sprintf (strout, "%s-prime-map", argv[1]);
  if ((out = open (strout, O_WRONLY | O_CREAT | O_TRUNC, 0664)) < 0)
    panic ("open");

  if ((mida = lseek (in, 0, SEEK_END)) < 0)
    panic ("lseek");
  nprocs = mida / 4;

  debug ("nprocs=%d\n", nprocs);

  for (i = 0; i < nprocs; i++)
    {
      switch (fork ())
	{
	case -1:
	  panic ("fork");

	case 0:
  	  if ((in = open (argv[1], O_RDONLY)) < 0)
            panic ("open");
	  if (lseek (in, (nprocs - i - 1) * 4, SEEK_SET) < 0)
	    panic ("lseek");
	  ret = read (in, &num, sizeof (int));
	  if (ret < sizeof (int))
	    panic ("partial read!!");
//	  debug ("Fill %d llegieix %d\n", i, num);

	  switch (fork ())
	    {
	    case 1:
	      panic ("fork");

	    case 0:
	      sprintf (strnum, "%d", num);
	      execlp ("./is_prime", "is_prime", strnum, NULL);
	      panic ("execlp");

	    default:
	      if (wait (&st) < 0)
		panic ("wait");
	      if (WIFEXITED (st))
		{
		  if (WEXITSTATUS (st) == 0)
		    c = '-';
		  else if (WEXITSTATUS (st) == 1)
		    c = 'p';
		  else
		    panic ("unexpected!!!");
		}
	      else
		panic ("unexpected!!!");
//	      debug ("Fill %d llegieix %d - result %c", i, num, c);

  	      if ((out = open (strout, O_WRONLY)) < 0)
                panic ("open");

//debug("fill %d escriu %c a %d (%d)", i, c, nprocs-i-1, num);

	      if (lseek(out, nprocs-i-1, SEEK_SET) < 0) panic("lseek");
	      if (write(out, &c, 1) < 0) panic("write");

              exit( WEXITSTATUS (st) );
	    }

	  exit (0);
	}
    }

    int total=0;
    for(i=0; i<nprocs; i++) {
	if (wait(&st) < 0) panic("wait");
	total += WEXITSTATUS(st);
    }

    if ((out = open (strout, O_WRONLY|O_APPEND)) < 0) panic("open");

    sprintf(strout, " %d\n", total);
    if (write(out, strout, strlen(strout))<0) panic("write");
}
