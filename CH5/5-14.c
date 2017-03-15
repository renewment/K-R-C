/*
 * Exercise 5-14: Modify the sort program to handle a -r flag, which indicates
 * sorting in reverse (decreasing) order. Be sure that -r works with -n.
 */

#include <stdio.h>
#include <string.h>

#define MAXLINES 5000       /* max #lines to be sorted */
char *lineptr[MAXLINES];    /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void quickSort(void *lineptr[], int left, int right, int reverse,
               int (*comp)(void *, void *));
int numcmp(char *, char *);

/* sort input lines */
main(int argc, char *argv[])
{
   int nlines;            /* number of input lines read */
   int numeric = 0,       /* 1 if numeric sort */
       reverse = 0;       /* descend order if reverse sort */
   char c;
   
   while (--argc && **++argv == '-') {
      c = *++*argv;
      switch (c) {
      case 'n':
         numeric = 1;
         break;
      case 'r':
         reverse = 1;
         break;
      default:
         goto error;
      }
   }
   if (argc) {
error:
      printf("Illegal option\n");
      printf("Usage: ./a.out -r -n\n");
      return -1;
   }
   
   if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
      quickSort((void **) lineptr, 0, nlines-1, reverse,
                (int (*)(void*,void*))(numeric ? numcmp : strcmp));
      writelines(lineptr, nlines);
      return 0;
   } else {
      printf("error: input too big to sort\n");
      return 1;
   }
}

#define MAXLEN 1000   /* maxlength of any input line */
int getLine(char *, int);
char *alloc(int);

/* readlines:  read input lines */
int readlines(char *lineptr[], int maxlines)
{
   int len, nlines;
   char *p, line[MAXLEN];
   
   nlines = 0;
   while ((len = getLine(line, MAXLEN)) > 0)
      if (nlines >= maxlines || (p = alloc(len)) == NULL)
         return -1;
      else {
         line[len-1] = '\0'; /* delete newline */
         strcpy(p, line);
         lineptr[nlines++] = p;
      }
   return nlines;
}


/* writelines:  write output lines */
void writelines(char *lineptr[], int nlines)
{
   int i;
   
   for (i = 0; i < nlines; i++)
      printf("%s\n", lineptr[i]);
}

/* quickSort:  sort v[left]...v[right] into increasing order */
void quickSort(void *v[], int left, int right, int reverse,
               int (*comp)(void *, void *))
{
   int i, last;
   void swap(void *v[], int, int);
   
   if (left >= right)   /* do nothing if array contains */
      return;           /* fewer than two elements */
   swap(v, left, (left + right)/2);
   last = left;
   if (!reverse) {
      for (i = left+1; i <= right; i++)
         if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
   } else
      for (i = left+1; i <= right; i++)
         if ((*comp)(v[i], v[left]) > 0)
            swap(v, ++last, i);
   swap(v, left, last);
   quickSort(v, left, last-1, reverse, comp);
   quickSort(v, last+1, right, reverse, comp);
}

#include <stdlib.h>

/* numcmp:  compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
   double v1, v2;
   
   v1 = atof(s1);
   v2 = atof(s2);
   if (v1 < v2)
      return -1;
   else if (v1 > v2)
      return 1;
   else
      return 0;
}

/* swap:  interchange v[i] and v[j] */
void swap(void *v[], int i, int j)
{
   void *temp;
   
   temp = v[i];
   v[i] = v[j];
   v[j] = temp;
}

/* getLine:  read a line into s, return length */
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

#define ALLOCSIZE 10000 /* size of available space */

static char allocbuf[ALLOCSIZE];  /* storage for alloc */
static char *allocp = allocbuf;   /* next free positin */

char *alloc(int n)  /* return pointer to n characters */
{
   if (allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */
      allocp += n;
      return allocp - n; /* old p */
   } else     /* not enough room */
      return 0;
}
