/*
 * Exercise 5-17: Add a field-handling capability, so sorting may be done on
 * fields within lines, each field sorted according to an independent set of
 * options. (The index for this book was sorted with -df for the index category
 * and -n for the page numbers.)
 *
 * Sorting starts from the first field, then second, and so on. Specify options
 * for each field. Fields are separate by two spaces. 
 */

#include <stdio.h>
#include <string.h>

#define MAXLINES 5000                 /* max #lines to be sorted */
#define MAXFIELD 10                   /* max # of field in each line */
char *lineptr[MAXLINES];              /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
char *alloc(int);

void quickSort(void *lineptr[], int left, int right, int nfields,
               int *numeric, int *fold, int *directory);

/* sort input lines */
int main(int argc, char *argv[])
{
   int nlines;                        /* number of input lines read */
   int nfields = 0;                   /* field index*/
   int numeric[MAXFIELD] = {0},       /* 1 if numeric sort */
       fold[MAXFIELD] = {0},          /* 1 if fold case */
       directory[MAXFIELD] = {0};     /* 1 if in directory order */
   char c;
   while (--argc && **++argv == '-') {
      while ((c = *++*argv))
         switch (c) {
         case 'n':
            numeric[nfields] = 1;
            break;
         case 'f':
            fold[nfields] = 1;
            break;
         case 'd':
            directory[nfields] = 1;
            break;
         default:
            goto error;
         }
      ++nfields;
   }
   if (argc) {
error:
      printf("Illegal option\n");
      printf("Usage: ./a.out -[nfd] [-nfd]\n");
      printf("each set of options for each field.\n");
      return -1;
   }
   if (!nfields)
      nfields = 1;
   if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
      quickSort((void **) lineptr, 0, nlines-1, nfields,
                numeric, fold, directory);
      writelines(lineptr, nlines);
	      return 0;
   } else {
      printf("error: input too big to sort\n");
      return 1;
   }
}

#define MAXLEN 1000   /* maxlength of any input line */
int getLine(char *, int);
int parseField(char *, char *);
char *foldCase(char *);
char *parsePunct(char *);
int myStrcmp(char *, char *);
int numcmp(char *, char *);

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
void quickSort(void *v[], int left, int right, int nfields,
               int *numeric, int *fold, int *directory)
{
   int i, last, fieldIndex, len;
   void swap(void *v[], int, int);
   char pivot[MAXLEN], current[MAXLEN],
        *p, *c;
   if (left >= right)   /* do nothing if array contains */
      return;           /* fewer than two elements */
   swap(v, left, (left + right)/2);
   last = left;
   for (i = left+1; i <= right; i++) {
      p = v[left];
      c = v[i];
      fieldIndex = 0;
      int result;
      do {
         len = parseField(pivot, p);
         if (*p)
            p += (len + 2);
         
         len = parseField(current, c);
         if (*c)
            c += (len + 2);
         
         if (fold[fieldIndex]) {
            foldCase(pivot);
            foldCase(current);
         }
         if (directory[fieldIndex]) {
            parsePunct(pivot);
            parsePunct(current);
         }
         result = (numeric[fieldIndex++]) ? numcmp(current, pivot) :
                                          myStrcmp(current, pivot);
      } while (!result && fieldIndex < nfields);
      
      if (result < 0)
         swap(v, last, i);
   }
   swap(v, left, last);
   quickSort(v, left, last-1, nfields, numeric, fold, directory);
   quickSort(v, last+1, right, nfields, numeric, fold, directory);
}

#include <stdlib.h>
#include <ctype.h>

/* get a field, which is separated by two spaces, from input */
int parseField(char *d, char *s)
{
   int len = 0;
   while (*s) {
      *d = *s++;
      if (*d == ' ' && *s == ' ') {       // if successive spaces
         *d = '\0';                       // return the length of current field
         return len;
      }
      ++d;
      ++len;
   }
   *d = '\0';
   return len;
}

/* foldCase:  convert all alphabet to lower case */
char *foldCase(char *d)
{
   char *r = d;
   while(*d)
      if (*d >= 'A' && *d <= 'Z')
         *d++ = *d - 'A' + 'a';
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

#define ALLOCSIZE 100000          /* size of available space */

static char allocbuf[ALLOCSIZE];  /* storage for alloc */
static char *allocp = allocbuf;   /* next free positin */

char *alloc(int n)                /* return pointer to n characters */
{
   if (allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */
      allocp += n;
      return allocp - n;          /* old p */
   } else                         /* not enough room */
      return 0;
}
