/*
 * Exercise 8-4: The standard library function
 *
 *    int fseek(FILE *fp, long offset, int origin)
 *
 * is identical to lseek except that fp is a file pointer instead of a file
 * descriptor and the return value is an int status, not a position. Write
 * fseek. Make sure that your fseek coordinates properly with the buffering 
 * done for the other function of the library.
 *
 *
 */

#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZ 1024

#ifndef OPEN_MAX
#define OPEN_MAX 20
#endif
typedef struct _iobuf {
   int  cnt;
   char *ptr;
   char *base;
   int  flag;
   int  fd;
} _FILE;

enum _flags {
   _READ   = 01,
   _WRITE  = 02,
   _UNBUF  = 04,
   _EOF    = 010,
   _ERR    = 020
};

_FILE _iob[OPEN_MAX] = {
   { 0, (char *) 0, (char *) 0, _READ, 0 },
   { 0, (char *) 0, (char *) 0, _WRITE, 1 },
   { 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2 },
};

int Strlen(char *);
int Fseek(_FILE *, long, int);

main (int argc, char *argv[])
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

int Fseek(_FILE *fp, long offset, int origin)
{
   int bufsize = fp->flag & _UNBUF ? 1 : BUFSIZ, r;
   if ((fp->flag&(_EOF|_ERR)))
      return EOF;
   if (lseek(fp->fd, offset, origin) < 0) {
      fp->flag |= _ERR;
      return EOF;
   } else
      if (fp->flag & _READ) {
         fp->ptr = fp->base;
         r = read(fp->fd, fp->base, bufsize);
         if (r > 0)
            return 0;
         else
            fp->flag = (r == 0) ? _EOF : _ERR;
         return EOF;
      }
}
