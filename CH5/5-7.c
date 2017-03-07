/*
 * Exercise 5-7: Rewrite readlines to store lines in an array supplied by main,
 * rather than calling alloc to maintain storage. How much faster is the
 * program?
 */

#include <stdio.h>
#include <string.h>

#define MAXLINES 5000
#define MAXLEN 1000
#define BUFSIZE MAXLINES * MAXLEN

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines, char *);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

main()
{
   int nlines;
   char buf[BUFSIZE];

   if ((nlines = readlines(lineptr, MAXLINES, buf)) >=0) {
      qsort(lineptr, 0, nlines-1);
      writelines(lineptr, nlines);
      return 0;
   } else {
      printf("error: input too big to sort\n");
      return 1;
   }
}

int getLine(char *, int);
char *alloc(int);

int readlines(char *lineptr[], int maxlines, char buf[])
{
   int len, nlines;
   char *p = buf, line[MAXLEN];
   
   nlines = 0;
   while ((len = getLine(line, MAXLEN)) > 0)
      if (nlines >= maxlines || p + len > buf + BUFSIZE)
         return -1;
      else {
         line[len-1] = '\0';  /* delete newline */
         strcpy(p, line);
         lineptr[nlines++] = p;
         p += len;
      }
   return nlines;
}

void writelines(char *lineptr[], int nlines)
{
   while (nlines-- > 0)
      printf("%s\n", *lineptr++);
}

int getLine(char s[], int lim)
{
   int c, i;
   
   for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
      s[i] = c;
   if (c == '\n') {
      s[i] = c;
      ++i;
   }
   s[i] = '\0';
   return i;
}

#define ALLOCSIZE 10000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n)
{
   if (allocbuf + ALLOCSIZE - allocp >= n) {
      allocp += n;
      return allocp - n;
   } else
      return 0;
}

void qsort(char *v[], int left, int right)
{
   int i, last;
   void swap(char *[], int i, int j);
   
   if (left >= right)
      return;
   swap(v, left, (left + right) / 2);
   last = left;
   for (i = left+1; i <=right; i++)
      if (strcmp(v[i], v[left]) < 0)
         swap(v, ++last, i);
   swap(v, left, last);
   qsort(v, left, last-1);
   qsort(v, last+1, right);
}

void swap(char *v[], int i, int j)
{
   char *temp;
   
   temp = v[i];
   v[i] = v[j];
   v[j] = temp;
}
