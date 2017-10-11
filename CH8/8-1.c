/*
 * Exercise 8-1: Rewrite the program cat from Chapter 7 using read, write, open
 * and close instead of their standard library equivalents. Perform experiments
 * to determine the relative speeds of the two versions.
 */

#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <stdio.h>

#define BUFSIZ 1024

int Strlen(char *);

main(int argc, char *argv[])
{
   int fd, n, e = 0;
   void filecopy(int, int);
   char *prog = argv[0];   /* program name for errors */
   char str[BUFSIZ];
   
   long start, end;
   start = clock();
   if (argc == 1)  /* no args; copy standard input */
      filecopy(0, 1);
   else
      while (--argc > 0)
         if ((fd = open(*++argv, O_RDONLY, 0)) == -1) {
            n = Strlen("cat: can't open ");
            write(2, "cat: can't open ", n);
            n = Strlen(*argv);
            write(2, *argv, n);
         } else {
            filecopy(fd, 1);
            close(fd);
         }
   end = clock();
   printf("time: %f\n", (double)(end - start) / (CLOCKS_PER_SEC));
   return 0;
}

int Strlen(char *s)
{
   int i;
   for (i = 0; *s; s++, i++)
      ;
   return i;
}

/* filecopy:  copy file ifp to file ofp */
void filecopy(int ifd, int ofd)
{
   char buf[BUFSIZ];
   int n;
   while ((n = read(ifd, buf, BUFSIZ)) > 0)
      write(ofd, buf, n);
}
