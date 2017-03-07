/*
 * Exercise 5-2: Write getfloat, the floating-point analog of getint. What type
 * does getfloat return as its function value?
 */

#include <stdio.h>
#include <ctype.h>

#define SIZE 10

int getch(void);
void ungetch(int);
int getfloat(double *);

main()
{
   int n;
   double array[SIZE] = {0.0};
   for (n = 0; n < SIZE && getfloat(&array[n]) != EOF; ++n)
      printf("%g ", array[n]);
   printf("\n");
   
   return 0;
}

int getfloat(double *pn)
{
   int c, counter;
   double sign, pow;
   
   while (isspace(c = getch()))
      ;
   if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
      ungetch(c);
      return 0;
   }
   sign = (c == '-') ? -1.0 : 1.0;
   if (c != '.') {
      if ( c == '+' || c == '-')
         c = getch();
      for (*pn = 0, counter = 0; isdigit(c); c = getch(), ++counter)
         *pn = 10.0 * *pn + (double)(c - '0');
      if (counter == 0) {
         ungetch((sign == 1) ? '+' : '-');
         return 0;
      }
   }
   pow = sign;
   if (c == '.')
      for (; isdigit(c = getch()); pow *= 10.0)
         *pn = 10 * *pn + (double)(c - '0');
   *pn /= pow;
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
