/*
 * Exercise 5-10: Write the program expr, which evaluates a reverse Polish
 * expression from the command line, where each operator or operand is a
 * separate argument. For example,
 *    expr  2  3  4  +  *
 * evaluates 2 x (3+4).
 *
 * There will be a problem when I try to multiply on my Mac (not sure whether so
 * on Linux). The parameter of '*' will be interpreted as all files in current
 * directory rather than normal asterisk.
 *
 * solution:
 * https://goo.gl/PqEHbH
 */

#include <stdio.h>
#include <stdlib.h>   /* for atof() */

void push(double);
double pop(void);

/* reverse Polish calculator */
main(int argc, char *argv[])
{
   int type;
   double op2;
   while (--argc > 0) {
      switch (*(++argv)[0]) {
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
      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9':
      case '.':
         push(atof(*argv));
         break;
      default:
         printf("error: unknown command %s\n", *argv);
         break;
      }
   }
   printf("\t%.8g\n", pop());
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
