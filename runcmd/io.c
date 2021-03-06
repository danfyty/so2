#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <runcmd.h>
#include <debug.h>

#define infile "in.txt"
#define outfile "out.txt"
#define errfile "err.txt"

int main (int argc, char **argv)
{
  int aux, fd;
  int errors = 0;
  char c;

  /* Try to read from standard input (infile) */
  aux = read (0,&c,1);
  errors += (aux<0) ? 1 : 0;
  errors += (c!='a') ? 1 : 0;

  /* Try to write to standard output (outfile) and read it again.*/
  aux = write (1,"b",1);
  errors += (aux<0) ? 1 : 0;
  close(1);
  sysfatal ((open ("/dev/null", O_WRONLY)) <0);

  sysfatal ((fd = open (outfile, O_RDONLY)) <0);
  aux = read (fd,&c,1);
  errors += (aux<0) ? 1 : 0;
  errors += (c!='b') ? 1 : 0;
  sysfatal (close(fd)<0);


  /* Try to write to standard error (errnfile) and read it again.*/
  aux = write (2,"c",1);
  errors += (aux<0) ? 1 : 0;
  close(2);
  sysfatal ((open ("/dev/null", O_WRONLY)) <0);

  sysfatal ((fd = open (errfile, O_RDONLY)) <0);
  aux = read (fd,&c,1);
  errors += (aux<0) ? 1 : 0;
  errors += (c!='c') ? 1 : 0;
  sysfatal (close(fd)<0);

  return errors;
}
