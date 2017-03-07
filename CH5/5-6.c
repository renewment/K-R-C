/*
 * Exercise 5-6: Rewrite appropriate programs from earlier chapters and
 * exercises with pointers instead of array indexing. Good possibilities include
 * getline (Chapters 1 and 4), atoi, itoa, and their variants (Chapters 2, 3,
 * and 4), reverse (Chapter 3), and strindex and getop (Chapter 4).
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 100
#define NUMBER '0'

int getLine(char *, int);
int atoi(char *);
void itoa(int, char *);
void reverse(char *);
int strindex(char *, char *);
int getop(char *);

main()
{
   return 0;
}

//modified getline in chapter 4
int getLine(char *s, int lim)
{
   int c, i;
   
   i= 0 ;
   while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
      *s++ = c;
   if (c == '\n')
      *s++ = c;
   *s = '\0';
   return i;
}

// modified atoi in chapter 3
int atoi(char *s)
{
   int i, n, sign;
   
   while (isspace(*s))
      s++;
   sign = (*s == '-') ? -1 : 1;
   if (*s == '+' || *s == '-')  /* skip sign */
      s++;
   for (n = 0; isdigit(*s); s++)
      n = 10 * n + (*s - '0');
   return sign * n;
}

// modified itoa in chapter 3
void itoa(int n, char *s)
{
   int i, sign;
   
   if ((sign = n) < 0)
      n = -n;
   i = 0;
   do
      *s++ = n % 10 + '0';
   while ((n /= 10) > 0);
   if (sign < 0)
      *s++ = '-';
   *s = '\0';
   reverse(s);
}

// modified reverse in chapter 3
void reverse(char *s)
{
   int c, i, j;
   
   for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
      c = *(s+i);
      *(s+i) = *(s+j);
      *(s+j) = c;
   }
}

// modified strindex in chapter 4
int strindex(char *s, char *t)
{
   int i;
   char *temp1, *temp2;
   for (i = 0; *s != '\0'; i++, s++) {
      for (temp1 = s, temp2 = t; *temp2!='\0' && *temp1==*temp2; temp1++, temp2++)
         ;
      if(temp2 > t && *temp2 == '\0')
         return i;
   }
   return -1;
}

int getch(void);
void ungetch(int);

int getop(char *s)
{
   int i, c;
   
   while ((*s = c = getch()) == ' ' || c == '\t')
      ;
   *(s+1) = '\0';
   if (!isdigit(c) && c != '.')
      return c;       /* not a number */
   i = 0;
   if (isdigit(c))    /* collect integer part */
      while (isdigit(*++s = c = getch()))
         ;
   if (c == '.')      /* collect fractin part */
      while (isdigit(*++s = c = getch()))
         ;
   *s = '\0';
   if (c != EOF)
      ungetch(c);
   return NUMBER;
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
