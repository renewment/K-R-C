/*
 * Exercise 5-16: Add the -d ("directory order") option, which makes comparisons
 * only on letters, numbers and blanks. Make sure it works in conjunction with
 * -f.
 *
 * My implementatin omits all of punctuations, like the format of index in K&R C
 * .
 */

#include <stdio.h>
#include <string.h>

#define MAXLINES 5000       /* max #lines to be sorted */
char *lineptr[MAXLINES];    /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
char *alloc(int);

void quickSort(void *lineptr[], char *formatted[], int left, int right,
               int (*comp)(void *, void *));
int myStrcmp(char *, char *);
int numcmp(char *, char *);
char *foldCase(char *, char *);
char *parsePunct(char *);

/* sort input lines */
main(int argc, char *argv[])
{
   int nlines;            /* number of input lines read */
   int numeric = 0,       /* 1 if numeric sort */
       fold = 0,          /* 1 if fold case */
       directory = 0;     /* 1 if in directory order */
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
         case 'd':
            directory = 1;
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
      char *formatted[nlines-1], *p;
      int i;
      for (i = 0; i < nlines; i++) {
         if (strlen(lineptr[i]) == 0)
            formatted[i] = p = alloc(1);
         else
            formatted[i] = p = alloc(strlen(lineptr[i]));
         if (formatted[i] == NULL)
            break;
         if (fold)
            foldCase(p, lineptr[i]);
         else
            strcpy(p, lineptr[i]);
         if (directory)
            parsePunct(p);
      }
      if (i < nlines) {
         printf("error, buffer is empty\n");
         return -1;
      }
      quickSort((void **) lineptr, formatted, 0, nlines-1,
                (int (*)(void*,void*))(numeric ? numcmp : myStrcmp));
      writelines(lineptr, nlines);
	      return 0;
   } else {
      printf("error: input too big to sort\n");
      return 1;
   }
}

#define MAXLEN 1000   /* maxlength of any input line */
int getLine(char *, int);

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
void quickSort(void *v[], char *formatted[], int left, int right,
               int (*comp)(void *, void *))
{
   int i, last;
   void swap(void *v[], int, int);
   char pivot[MAXLEN], current[MAXLEN];

   if (left >= right)   /* do nothing if array contains */
      return;           /* fewer than two elements */
   swap(formatted, left, (left + right)/2);
   swap(v, left, (left + right)/2);
   last = left;
   int d;
   for (i = left+1; i <= right; i++) {
      if ((d=(*comp)(formatted[i], formatted[left])) < 0) {
         swap(formatted, ++last, i);
         swap(v, last, i);
      }
   }
   swap(formatted, left, last);
   swap(v, left, last);
   quickSort(v, formatted, left, last-1, comp);
   quickSort(v, formatted, last+1, right, comp);
}

#include <stdlib.h>
#include <ctype.h>

/* myStrcmp: compare s1 and s2 numerically without converting unsigneed */
int myStrcmp(char *s1, char *s2)
{
   for (; *s1 == *s2; ++s1, ++s2)
      if (*s1 == '\0')
         return 0;
   return *s1 - *s2;
}

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
char *foldCase(char *d, char *s)
{
   char *r = d;
   while(*s)
      *d++ = (*s >= 'A' && *s <= 'Z') ? *s++ - 'A' + 'a' : *s++;
   *d = '\0';
   return r;
}

/* parsePunct character value for sorting in directory order */
char *parsePunct(char *s)
{
   char *r, *next;
   r = next = s;
   while (*next)
      if (!ispunct(*next)) {
         *s++ = *next++;
      } else
         next++;
   *s = '\0';
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
   if (c == '\n')
      s[i++] = c;
   s[i] = '\0';
   return i;
}

#define ALLOCSIZE 100000 /* size of available space */

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
