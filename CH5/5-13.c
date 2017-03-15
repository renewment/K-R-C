/*
 * Exercise 5-13: Write the program tail, which prints the last n lines of its
 * input. By default, n is 10, let us say, but it can be changed by an optional
 * argument, so that
 *      tail -n
 * prints the last n lines. The program should behave rationally no matter how
 * unreasonable the input or the value of n. Write the program so it makes the
 * best use of available storage; lines should be stored as in the sorting
 * program of Section 5.6, not in a two-dimensinal array of fixed size.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000
#define N 10

int readlines(char *[], int nlines);
void writelines(char *[], int nlines, int n);// this functin should be modified

main(int argc, char *argv[])
{
   int n = N, nlines;
   char *lineptr[MAXLINES];
   if (--argc && **++argv == '-')
      n = atoi(++*argv);
   if (argc > 1) {
      printf("Illegal options\n");
      printf("Usage: ./a.out [-n]\n");
      return -1;
   }
   if ((nlines = readlines(lineptr, MAXLINES)) >= 0)
      writelines(lineptr, nlines, n);
   else {
      printf("error: input too long\n");
      return -1;
   }
   return 0;
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
void writelines(char *lineptr[], int nlines, int n)
{
   int i;
   for (i = nlines - n; i < nlines; i++)
      printf("%s\n", lineptr[i]);
}

/* getLine:  get line into s, return length */
int getLine(char s[], int lim)
{
   int c, i;
   
   i= 0 ;
   while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
      s[i++] = c;
   if (c == '\n')
      s[i++] = c;
   s[i] = '\0';
   return i;
}

#define ALLOCSIZE 10000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

char *alloc(int n)  /* return pointer to n characters */
{
   if (allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */
      allocp += n;
      return allocp - n; /* old p */
   } else     /* not enough room */
      return 0;
}

void afree(char *p)
{
   if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
      allocp = p;
}
