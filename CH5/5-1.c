/*
 * Exercise 5-1: As written, getint treats a + or - not followed by a digit as a
 * valid representation of zero. Fix it to push such a character back on the
 * input.
 */

#include <stdio.h>
#include <ctype.h>

#define SIZE 10

int getch(void);
void ungetch(int);
int getint(int *);

main()
{
   int n, array[SIZE] = {0}, getint(int *);
   
   for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
      printf("%d ", array[n]);
   printf("\n");
   return 0;
}

int getint(int *pn)
{
   int c, sign, counter;
   
   while (isspace(c = getch()))
      ;
   if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
      ungetch(c);
      return 0;
   }
   sign = (c == '-') ? -1 : 1;
   if ( c == '+' || c == '-')
      c = getch();
   for (*pn = 0, counter = 0; isdigit(c); c = getch(), ++counter)
      *pn = 10 * *pn + (c - '0');
   if (counter == 0) {
      ungetch((sign == 1) ? '+' : '-');
      return 0;
   }
   *pn *= sign;
   if (c != EOF)
      ungetch(c);
   return c;
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
