/*
 * Exercise 5-15: Add the option -f to fold upper and lower cae together, so
 * that case distinctions are not made during sorting: for example, a and A 
 * compare equal.
 */

#include <stdio.h>
#include <string.h>

#define MAXLINES 5000       /* max #lines to be sorted */
char *lineptr[MAXLINES];    /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void quickSort(void *lineptr[], int left, int right,
               char *(*fold)(char *, const char *),
               int (*comp)(void *, void *));
int numcmp(char *, char *);
char *foldCase(char *, const char *);

/* sort input lines */
main(int argc, char *argv[])
{
   int nlines;            /* number of input lines read */
   int numeric = 0,       /* 1 if numeric sort */
       fold = 0;          /* 1 if fold case */
   char c;
   
   while (--argc && **++argv == '-') {
      while (c = *++*argv)
         switch (c) {
         case 'n':
            numeric = 1;
            break;
         case 'f':
            fold = 1;
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
      quickSort((void **) lineptr, 0, nlines-1,
                (char *(*)(char*,const char*))(fold ? foldCase : strcpy),
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
void quickSort(void *v[], int left, int right,
               char *(*fold)(char *, const char *),
               int (*comp)(void *, void *))
{
   int i, last;
   void swap(void *v[], int, int);
   char pivot[MAXLEN], current[MAXLEN];
   
   if (left >= right)   /* do nothing if array contains */
      return;           /* fewer than two elements */
   swap(v, left, (left + right)/2);
   last = left;
   (*fold)(pivot , v[left]);
   for (i = left+1; i <= right; i++) {
      if ( (*comp)((*fold)(current, v[i]), pivot) < 0 )
         swap(v, ++last, i);
   }
   swap(v, left, last);
   quickSort(v, left, last-1, fold, comp);
   quickSort(v, last+1, right, fold, comp);
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

/* foldCase:  convert all alphabet to lower case */
char *foldCase(char *d, const char *s)
{
   char *r = d;
   while(*s)
      *d++ = (*s >= 'A' && *s <= 'Z') ? *s++ - 'A' + 'a' : *s++;
   *d = '\0';
   return r;
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
