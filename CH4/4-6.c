/*
 * Exercise 4-6: Add command for handling variables. (It's easy to provide
 * twenty-six variables with single-letter names.) Add a variable for the most
 * recently printed value.
 */

#include <stdio.h>
#include <stdlib.h>   /* for atof() */

#define MAXOP   100   /* max size of operand or operator */
#define NUMBER  '0'   /* signal that a number was found */

#define VARIABLE 'V'  /* signal for variable handling */
#define VARIABLELENGTH 26 /* 26 variables named by single lower-case letter */
#define LAST 'L'      /* read last printed value */
double variable[VARIABLELENGTH];
int useFlag[VARIABLELENGTH];      /* specify if variables have been used */
double last;

int getop(char []);
void push(double);
double pop(void);

void parseVariable(char []);
void writeVariable(double);
double readVariable(void);
void writeLast(double);
void readLast(void);

/* reverse Polish calculator */
main()
{
   int type, i;
   double op2, value;
   char s[MAXOP];
   
   for (i = 0; i < VARIABLELENGTH; ++i)
      useFlag[i] = 0;
   
   while ((type = getop(s)) != EOF) {
         switch (type) {
         case VARIABLE:
            parseVariable(s);
            break;
         case LAST:
            readLast();
            break;
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
         case 'W':
               writeVariable(pop());
               break;
         case 'R':
               push(readVariable());
               break;
         case 'P':
               break;
         case '\n':
            value = pop();
            writeLast(value);
            printf("\t%.8g\n", value);
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
   if (c >= 'a' && c <= 'z')
      return VARIABLE;
   else if (c == 'L')
      return LAST;
   else if (!isdigit(c) && c != '.')
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

int variableIndex = -1;
void parseVariable(char s[])
{
   variableIndex = s[0] - 'a';
}

void writeVariable(double value)
{
   if (variableIndex != -1) {
      variable[variableIndex] = value;
      variableIndex = -1;
   }
   else
      printf("error, variable name needs to be specified\n");
}

double readVariable(void)
{
   double value;
   if (variableIndex != -1) {
      value = variable[variableIndex];
      variableIndex = -1;
      return value;
   }
   else
      printf("error, variable name needs to be specified\n");
   return 0.0;
}

double last = 0;

void writeLast(double value)
{
   last = value;
}

void readLast(void)
{
   push(last);
}
