/*
 * Exercise 6-1: Our version of getword does not properly handle underscores,
 * string constants, comments, or preprocessor control lines. Write a better
 * version.
 *
 * My version only counts keywords of basic types and suppposes input is
 * syntactically and grammatically correct.
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

struct key {
   char *word;
   int count;
} keytab[] = {
   "char", 0,
   "double", 0,
   "float", 0,
   "int", 0,
   "long", 0,
   "shot", 0,
   "signed", 0,
   "unsigned", 0,
   "void", 0,
};

#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof(keytab[0]))

int getword(char *, int);
int binsearch(char *, struct key *, int);

/* count C keywords */
main()
{
   int n;
   char word[MAXWORD];
   
   while (getword(word, MAXWORD) != EOF)
      if (isalpha(word[0]))
         if ((n = binsearch(word, keytab, NKEYS)) >= 0)
            keytab[n].count++;
   for (n = 0; n < NKEYS; n++)
      if (keytab[n].count > 0)
         printf("%4d %s\n",
                keytab[n].count, keytab[n].word);
   return 0;
}

/* binsearch:  find word in tab[0]...tab[n-1] */
int binsearch(char *word, struct key tab[], int n)
{
   int cond;
   int low, high, mid;
   
   low = 0;
   high = n - 1;
   while (low <= high) {
      mid = (low+high) / 2;
      if ((cond = strcmp(word, tab[mid].word)) < 0)
         high = mid - 1;
      else if (cond > 0)
         low = mid + 1;
      else
         return mid;
   }
   return -1;
}

/* getword:  get next word or character from input */
int getword(char *word, int lim)
{
   int c, nextC, getch(void), isString;
   void ungetch(int);
   char *w = word;
   isString = 0;
   
   while (isspace(c = getch()))
      ;
   if (c != EOF)
      *w++ = c;
   if (!isalpha(c) && // check alpha
       c != '_' &&    // check underscore
       c != '\"' &&   // check string constant
       c != '/' &&    // check start of line or block comment
       c != '*' &&    // check end of block comment
       c != '#') {    // check preprocessor control
      *w = '\0';
      return c;
   }
   if (c == '\"')
      isString = 1;
   if (c == '/') {
      if ((nextC=getch()) == '/') {       // if this word is //....//
         *w++ = nextC;
         while ((c=getch()) == '/')
            *w++ = c;
         ungetch(c);
         *w = '\0';
      } else if (nextC == '*') {          // if this word is started by /*
         *w++ = nextC;
         while ((c=getch()) == '*')       // when there are consequent *
            *w++ = c;
         if (w - word > 2 && c == '/')    // if w record more than 3 char,
            *w++ = c;                     // i.e. w = "/*...*" and the last c is
         *w = '0';                        // '/', so this word will be /*...*/
      } else
         ungetch(nextC);                  // slash for division
      return word[0];
   }
   if (c == '*') {
      if ((nextC=getch()) == '/') {       // w is */
         *w++ = nextC;
      } else
         ungetch(nextC);
      *w = '\0';
      return word[0];
   }
   for ( ; --lim > 0; w++) {
      if (!isalnum(*w = getch()) &&       // check alpha or number
                   *w != '_' &&           // check underscore
                   *w != '\"') {          // check string constant
         ungetch(*w);
         break;
      }
      if (*w == '\"')                     // end of strint constant is read
         break;
   }
   *w = '\0';
   return word[0];
}

#define BUFSIZE 100

char buf[BUFSIZE];  /* buffer for ungetch */
int  bufp = 0;      /* next free position in buf */

int getch(void) /* get a (possibly pushed back) character */
{
   return (bufp > 0) ? buf[--bufp] :  getchar();
}

void ungetch(int c) /* push character back on input */
{
   if (bufp >= BUFSIZE)
      printf("ungetch: too many characters\n");
   else
      buf[bufp++] = c;
}
