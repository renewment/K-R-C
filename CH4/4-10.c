/*
 * Exercise 4-10: An alternate organization uses getline to read an entrie input
 * line; this makes getch and ungetch unnecessary. Revise the calculator to use
 * this approach.
 */

#include <stdio.h>
#include <stdlib.h>   /* for atof() */

#define MAXOP   100   /* max size of operand or operator */
#define NUMBER  '0'   /* signal that a number was found */
#define BUFSIZE 100

char buf[BUFSIZE];
int  bufp = 0;      /* next free position in buf */

int getop(char []);
void push(double);
double pop(void);
int getLine(char [], int);

/* reverse Polish calculator */
main()
{
   int type, length;
   double op2;
   char s[MAXOP];
   
   while ((length=getLine(buf, BUFSIZE)) != 0) {
      do {
         switch (type = getop(s)) {
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
            case '\n':
               printf("\t%.8g\n", pop());
               break;
            default:
               printf("error: unknown command %s\n", s);
               break;
         }
      } while (bufp < length);
      bufp = 0;
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

#include <ctype.h>

/* getop:  get next operator or numeric operand */
int getop(char s[])
{
   int i, c;
   
   do
      s[0] = c = buf[bufp++];
   while (c == ' ' || c == '\t');
   s[1] = '\0';
   if (!isdigit(c) && c != '.')
      return c;       /* not a number */
   i = 0;
   if (isdigit(c))    /* collect integer part */
      while (isdigit(s[++i] = c = buf[bufp++]))
         ;
   if (c == '.')      /* collect fractin part */
      while (isdigit(s[++i] = c = buf[bufp++]))
         ;
   s[i] = '\0';
   if (c != EOF)
      --bufp;
   return NUMBER;
}

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
