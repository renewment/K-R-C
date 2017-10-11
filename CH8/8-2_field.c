/*
 * Exercise 8-2: Rewrite fopen and _fillbuf with fields instead of explicit bit
 * operations. Compare code size and execution speed.
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
#undef getc
#undef getchar
#define getc(p)   (--(p)->cnt >= 0\
               ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define getchar()   getc(stdin)

struct _flags {
   unsigned int _READ  : 1;
   unsigned int _WRITE : 1;
   unsigned int _UNBUF : 1;
   unsigned int _EOF   : 1;
   unsigned int _ERR   : 1;
};

typedef struct _iobuf {
   int  cnt;
   char *ptr;
   char *base;
   struct _flags flag;
   int  fd;
} _FILE;

_FILE _iob[OPEN_MAX] = {
   { 0, (char *) 0, (char *) 0, {1, 0, 0, 0, 0}, 0 },
   { 0, (char *) 0, (char *) 0, {0, 1, 0, 0, 0}, 1 },
   { 0, (char *) 0, (char *) 0, {0, 1, 1, 0, 0}, 2 },
};

_FILE *Fopen(char *, char *);
int _fillbuf(_FILE *);
int Strlen(char *);

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

#define PERMS 0666
_FILE *Fopen(char *name, char *mode)
{
   int fd;
   _FILE *fp;
   
   if (*mode != 'r' && *mode != 'w' && *mode != 'a')
      return NULL;
   for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
      if (fp->flag._READ == 0 && fp->flag._WRITE == 0)
         break;
   if (fp >= _iob + OPEN_MAX)
      return NULL;
   
   if (*mode == 'w')
      fd = creat(name, PERMS);
   else if (*mode == 'a') {
      if ((fd = open(name, O_WRONLY, 0)) == -1)
         fd = creat(name, PERMS);
      lseek(fd, 0L, 2);
   } else
      fd = open(name, O_RDONLY, 0);
   if (fd == -1)
      return NULL;
   fp->fd = fd;
   fp->cnt = 0;
   fp->base = NULL;
   if (*mode == 'r')
      fp->flag._READ = 1;
   else
      fp->flag._WRITE = 1;
   return fp;
}

/* _fillbuf:  allocate and fill input buffer */
int _fillbuf(_FILE *fp)
{
   int bufsize;
   
   if (!(fp->flag._READ) || fp->flag._EOF || fp->flag._ERR)
      return EOF;
   bufsize = fp->flag._UNBUF ? 1 : BUFSIZ;
   if (fp->base == NULL)    /* no buffer yet */
      if ((fp->base = (char *) malloc(bufsize)) == NULL)
         return EOF;        /* can't get buffer */
   fp->ptr = fp->base;
   fp->cnt = read(fp->fd, fp->ptr, bufsize);
   if (--fp->cnt < 0) {
      if (fp->cnt == -1)
         fp->flag._EOF = 1;
      else
         fp->flag._ERR = 1;
      fp->cnt = 0;
      return EOF;
   }
   return (unsigned char) *fp->ptr++;
}
