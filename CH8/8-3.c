/*
 * Exercise 8-3: Design and write _flushbuf, fflush, and fclose.
 */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#undef BUFSIZ
#define BUFSIZ 100

#undef  stdin
#undef  stdout
#undef  stderr
#define stdin  (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

#ifndef OPEN_MAX
#define OPEN_MAX 20
#endif

#undef feof
#define feof(p)  (((p)->flag & _EOF) != 0)

#undef getc
#define getc(p)   (--(p)->cnt >= 0\
               ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#undef getchar
#define getchar()   getc(stdin)

#undef putc
#define putc(x,p)   (--(p)->cnt >= 0 \
               ? *(p)->ptr++ = (x) : _flushbuf((x),p))
#undef putchar
#define putchar(x)  putc((x), stdout)
 
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

_FILE *Fopen(char *, char *);
int Fclose(_FILE *);
int _fillbuf(_FILE *);
int _flushbuf(int, _FILE *);
int Fflush(_FILE *);
int Strlen(char *);

main (int argc, char *argv[])
{
   int fd, n, e = 0, iter = 0;
   char c;
   _FILE *fpo = Fopen(*++argv, "w");
   --argc;
   while (--argc) {
      _FILE *fp = Fopen(*++argv, "r");
      while (!feof(fp)) {
         c = getc(fp);
         //putc(c, stdout);
         putc(c, fpo);
      }
      Fclose(fp);
      putc('\n', fpo);
   }
   Fclose(fpo);
   //sleep(2);
   return 0;
}

int Strlen(char *s)
{
   int i;
   for (i = 0; *s; s++, i++)
      ;
   return i;
}

#define PERMS 0666
_FILE *Fopen(char *name, char *mode)
{
   int fd;
   _FILE *fp;
   
   if (*mode != 'r' && *mode != 'w' && *mode != 'a')
      return NULL;
   for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
      if ((fp->flag & (_READ|_WRITE)) == 0)
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
   fp->flag = (*mode == 'r') ? _READ : _WRITE;
   return fp;
}

int Fclose(_FILE *fp)
{
   if ((fp->flag&(_READ|_EOF)) == (_READ|_EOF) && (fp->flag&_ERR) == 0)
      _flushbuf(EOF, stdout);
   else if ((fp->flag&_WRITE) == _WRITE && (fp->flag&_ERR) == 0){
      _flushbuf(EOF, fp);
   }
   fp->cnt = 0;
   fp->ptr = NULL;
   free(fp->base);
   fp->flag = 0;
   return close(fp->fd);
}

/* _fillbuf:  allocate and fill input buffer */
int _fillbuf(_FILE *fp)
{
   int bufsize;
   
   if ((fp->flag&(_READ|_EOF|_ERR)) != _READ)
      return EOF;
   bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
   if (fp->base == NULL)    /* no buffer yet */
      if ((fp->base = (char *) malloc(bufsize)) == NULL)
         return EOF;        /* can't get buffer */
   fp->ptr = fp->base;
   fp->cnt = read(fp->fd, fp->ptr, bufsize);
   if (--fp->cnt < 0) {
      if (fp->cnt == -1)
         fp->flag |= _EOF;
      else
         fp->flag |= _ERR;
      fp->cnt = 0;
      return EOF;
   }
   return (unsigned char) *fp->ptr++;
}

/* use system call "write" to flush buffer */
int _flushbuf(int c, _FILE *fp)
{
   int bufsize, w;
   if ((fp->flag&(_WRITE|_EOF|_ERR)) != _WRITE)
      return EOF;
   bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
   if (fp->base == NULL)
      if ((fp->base = (char *) malloc(bufsize)) == NULL)
         return EOF;
   if (fp->ptr) {
      if ((w=write(fp->fd, fp->base, bufsize - fp->cnt + 1)) <= 0) {
         if (w == 0)
            fp->flag |= _EOF;
         else if (w < 0)
            fp->flag |= _ERR;
         return EOF;
      }
   }
   fp->ptr = fp->base;
   fp->cnt = bufsize;
   if (c != EOF) {
      *fp->ptr = (char) c;
      return write(fp->fd, fp->base, 1);
   } else
      return 0;
}

int Fflush(_FILE *fp)
{
   size_t offset = fp->ptr - fp->base;
   int f;
   if (fp->flag|(_EOF|_ERR))
      return EOF;
   if (fp->flag|_WRITE)
      if ((f=write(fp->fd, fp->base, offset)) < 0) {
         fp->flag |= _ERR;
         fp->cnt = 0;
         return EOF;
      }
   fp->cnt = fp->flag & _UNBUF ? 1 : BUFSIZ;
   fp->ptr = fp->base;
   return 0;
}
