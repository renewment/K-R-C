/*
 * Exercise 4-5: Add access to library functions like sin, exp, and pow. See
 * <math.h> in Appendix B, Section 4.
 */

#include <stdio.h>
#include <stdlib.h>   /* for atof() */
#include <math.h>

#define MAXOP   100   /* max size of operand or operator */
#define NUMBER  '0'   /* signal that a number was found */

int getop(char []);
void push(double);
double pop(void);
int isint(double);

/* reverse Polish calculator */
main()
{
   int type;
   double op1, op2;
   char s[MAXOP];
   
   while ((type = getop(s)) != EOF) {
      switch (type) {
      case NUMBER:
         push(atof(s));
         break;
      case '+':
         push(pop() + pop());
         break;
      case '*':
         push(pop() * pop());
         break;
      case '-':
         op2 = pop();
         push(pop() - op2);
         break;
      case '/':
         op2 = pop();
         if (op2 != 0.0)
            push(pop() / op2);
         else
            printf("error: zero divisor\n");
         break;
      case 's':
         push(sin(pop()));
         break;
      case 'e':
         push(exp(pop()));
         break;
      case 'p':
         op2 = pop();
         op1 = pop();
         if ((op1 == 0 && op2 <= 0)  || (op1 < 0 && !isint(op2)))
            printf("domain error\n");
         else
            push(pow(op1, op2));
         break;
      case '\n':
         printf("\t%.8g\n", pop());
         break;
      default:
         printf("error: unknown command %s\n", s);
         break;
      }
   }
   return 0;
}

#define MAXVAL  100   /* maximum depth of val stack */

int sp = 0;           /* next free stack position */
double val[MAXVAL];   /* value stack */

/* push:  push f onto value stack */
void push(double f)
{
   if (sp < MAXVAL)
      val[sp++] = f;
   else
      printf("error: stack full, can't push %g\n", f);
}

/* pop:  pop a nd return top value from stack */
double pop(void)
{
   if (sp > 0)
      return val[--sp];
   else {
      printf("error: stack empty\n");
      return 0.0;
   }
}

int isint(double op)
{
   int tmp = op;
   return op == (double)tmp ? 1 : 0;
}

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop:  get next operator or numeric operand */
int getop(char s[])
{
   int i, c;
   
   while ((s[0] = c = getch()) == ' ' || c == '\t')
      ;
   s[1] = '\0';
   if (!isdigit(c) && c != '.')
      return c;       /* not a number */
   i = 0;
   if (isdigit(c))    /* collect integer part */
      while (isdigit(s[++i] = c = getch()))
         ;
   if (c == '.')      /* collect fraction part */
      while (isdigit(s[++i] = c = getch()))
         ;
   s[i] = '\0';
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
