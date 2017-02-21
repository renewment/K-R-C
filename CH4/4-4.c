/*
 * Exercise 4-4: Add commands to print the top element of the stack without
 * popping, to duplicate it, and to swap the top two elements. Add a command to
 * clear the stack.
 */

#include <stdio.h>
#include <stdlib.h>   /* for atof() */

#define MAXOP   100   /* max size of operand or operator */
#define NUMBER  '0'   /* signal that a number was found */

int getop(char []);
void push(double);
double pop(void);
void print(void);     /* print the top element of the stack */
void duplicate(void); /* duplicate the top element of the stack */
void swap(void);      /* swap the top two elements of the stack */

/* reverse Polish calculator */
main()
{
   int type;
   double op2;
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
      case 'p':
         print();
         break;
      case 'd':
         duplicate();
         break;
      case 's':
         swap();
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

void print()
{
   if (sp > 0)
      printf("the top element in stack is %g\n", val[sp-1]);
   else
      printf("error: stack is empty\n");
}

void duplicate()
{
   if (sp > 0) {
      val[sp] = val[sp-1];
      ++sp;
   }
   else
      printf("error: stack is empty\n");
}

void swap()
{
   double tmp;
   if (sp > 1) {
      tmp = val[sp-1];
      val[sp-1] = val[sp-2];
      val[sp-2] = tmp;
   }
   else
      printf("error: there need to be two or more numbers in stack\n");
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
