/*
 * Exercise 4-7: Write a routine ungets(s) that will push back an entire string
 * onto the input. Should ungets know about buf and bufp, or should it just use
 * ungetch?
 */

#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100

int getch(void);
void ungetch(int);
void ungets(char []);

char buf[BUFSIZE];  /* buffer for ungetch */
int  bufp = 0;      /* next free position in buf */

main()
{
   char s[] = "abcdefghijklmnopqrstuvwxyz\n";
   char c;
   ungets(s);
   while ((c = getch()) != '\0') {
      putchar(c);
   }
   return 0;
}

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

void ungets(char s[])
{
   int i;
   for (i = 0; s[i] != '\0'; ++i)
      ;
   for (; i >= 0; --i)
      ungetch(s[i]);
}
