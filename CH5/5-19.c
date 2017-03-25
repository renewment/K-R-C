/*
 * Exercise 5-19: Modify undcl so that it does not add redundant parentheses to
 * declarations.
 *
 *    *a()        -> a () *
 *    (*a)()      -> a * ()
 *
 *    *a[]        -> a [] *
 *    (*a)[]      -> a * []
 *
 *    *a()[]      -> a () [] *
 *    (*a())[]    -> a () * []
 *
 *    *a()()      -> a () () *  
 *                a is a function returning function returning pointer to int?
 *    (*a())()    -> a () * ()
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define  MAXTOKEN  100

enum { NAME, PARENS, BRACKETS };

int  gettoken(void);
int  tokentype;           /* type of last token */
char token[MAXTOKEN];     /* last token string */
char name[MAXTOKEN];      /* identifier name */
char datatype[MAXTOKEN];  /* data type = char, int, etc. */
char out[1000];           /* output string */

int lookAhead(void);     /* read the next token */

/* undcl:  convert word description to declaration */
main()
{
   int type, nextType, errorFlag = 0;
   char temp[MAXTOKEN];
   
   while (gettoken() != EOF) {
      strcpy(out, token);
      while ((type = gettoken()) != '\n') {
         if (type == PARENS || type == BRACKETS)
            strcat(out, token);
         else if (type == '*') {
            nextType = lookAhead();
            if (nextType == PARENS || nextType == BRACKETS)
               sprintf(temp, "(*%s)", out);
            else
               sprintf(temp, "*%s", out);
            strcpy(out, temp);
         } else if (type == NAME) {
            sprintf(temp, "%s %s", token, out);
            strcpy(out, temp);
         } else {
            printf("invalid input at %s\n", token);
            while (tokentype != '\n')
               gettoken();
            errorFlag = 1;
         }
         if (errorFlag)
            break;
      }
      if (errorFlag)
         errorFlag = 0;
      else
         printf("%s\n", out);
   }
   return 0;
}

int getch(void);
void ungetch(int);

int lookAhead(void) /* lookAhead */
{
   int c;
   while ((c = getch()) == ' ' || c == '\t')
      ;
   ungetch(c);
   if (c == '(')
      return PARENS;
   else if (c == '[')
      return BRACKETS;
   else
      return c;
}

int gettoken(void)  /* return next token */
{
   int c;
   char *p = token;
   
   while ((c = getch()) == ' ' || c == '\t')
      ;
   if (c == '(') {
      if ((c = getch()) == ')') {
         strcpy(token, "()");
         return tokentype = PARENS;
      } else {
         ungetch(c);
         strcpy(token, "(");
         return tokentype = '(';
      }
   } else if (c == '[') {
      for (*p++ = c; (*p++ = getch()) != ']'; )
         ;
      *p = '\0';
      return tokentype = BRACKETS;
   } else if (isalpha(c)) {
      for (*p++ = c; isalnum(c = getch()); )
         *p++ = c;
      *p = '\0';
      ungetch(c);
      return tokentype = NAME;
   } else {
      *p++ = c;
      *p = '\0';
      return tokentype = c;
   }
}

#define BUFSIZE 100
char buf[BUFSIZE];  /* buffer for ungetch */
int  bufp = 0;      /* next free position in buf */

int getch(void) /* get a (possibly pushed back) character */
{
   return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
   if (bufp >= BUFSIZE)
      printf("ungetch: too many characters\n");
   else
      buf[bufp++] = c;
}
