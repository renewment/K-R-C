/*
 * Exercise 5-20: Expand dcl to handle declarations with function argument types
 * , qualifiers like const, and so on.
 *
 * dcl:         optinal *'s direct-dcl
 * direct-dcl:  name
 *              (dcl)
 *              direct-dcl(optional args)
 *              direct-dcl[optional size]
 * args:        type dcl [, args]
 * type:        [optional qualifier] type
 * qualifiers:  [const | volatile]
 * type:        [void | char | short | int | long | float |
 *               double | signed | unsigned]
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define  MAXTOKEN  100

enum { NAME, PARENS, BRACKETS, QUALIFIER, VARIABLETYPE };

void dcl(void);
void dirdcl(void);

int  gettoken(void);
int  tokentype;           /* type of last token */
char token[MAXTOKEN];     /* last token string */
char name[MAXTOKEN];      /* identifier name */
char datatype[MAXTOKEN];  /* data type = char, int, etc. */
char out[1000];           /* output string */

void args(void);
char *qualifiers[] = {"const", "volatile"};
char *types[] = {"void",
                "char", "short",   /* can be preceeded by "signed" */
                "int", "long",     /* or "unsigned" */
                "float", "double",
                "signed", "unsigned"};
int debug = 0;
int parseArg = 0;

main()  /* convert declaration to words */
{
   while (gettoken() != EOF) {  /* 1st token on line */
      strcpy(datatype, token);  /* is the datatype */
      out[0] = '\0';
      dcl();      /* parse rest of ine */
      if (tokentype != '\n') {
         printf("syntax error\n");
         while (tokentype != '\n')
            gettoken();
         continue;
      }
      printf("%s: %s %s\n\n", name, out, datatype);
   }
   return 0;
}

/* dcl:  parse a declarator */
void dcl(void)
{
   int ns;
   
   for (ns = 0; gettoken() == '*'; )   /* count *'s */
      ns++;
   dirdcl();
   while (ns-- > 0)
      strcat(out, " pointer to");
}

/* dirdcl:  parse a direct declarator */
void dirdcl(void)
{
   int type;
   
   if (tokentype == '(') {        /* ( dcl ) */
      dcl();
      if (tokentype != ')') {
         printf("error: missing )\n");
         return;
      }
   } else if (tokentype == NAME && !parseArg)  /* variable name */
      strcpy(name, token);
   else if (tokentype == NAME)                 /* argument name */
      ;
   else if (tokentype == PARENS && parseArg)
      strcat(out, " function returning");
   else if (tokentype == BRACKETS && parseArg) {
      strcat(out, " array");
      strcat(out, token);
      strcat(out, " of");
   } else if (tokentype == ')' || tokentype == ',') {
      return ;
   }else {
      printf("error: expected name or (dcl)\n");
      return;
   }
   while ((type=gettoken()) == PARENS || type == BRACKETS || type == '(')
      if (type == PARENS)
         strcat(out, " function returning");
      else if (type == BRACKETS) {
         strcat(out, " array");
         strcat(out, token);
         strcat(out, " of");
      } else {                   /* deel with arguments of function */
         strcat(out, " function, taking");
         args();
         if (tokentype != ')') {
            printf("error: missing )\n");
            return ;
         }
         strcat(out, " as argument, returning");
      }
}

int parseType(char*);

/* args:  parse function arguments */
void args(void)
{
   int t;
   char argType[50] = "";
   if (!parseType(argType)) {                         /* variable type- */
      parseArg = 1;
      dcl();
      parseArg = 0;
      strcat(out, " ");
      strcat(out, argType);
      if (tokentype == ',') {
         strcat(out, " and");
         args();
      }
    } else
       printf("wrong type");
}

int parseType(char *s)
{
   int t;
   debug = 1;
   if ((t=gettoken()) == QUALIFIER) {
      strcat(out, " ");
      strcat(out, token);
      if ((t=gettoken()) == VARIABLETYPE) {
         strcat(s, " ");
         strcat(s, token);
         return 0;
      } else {
         printf("error, expected data type\n");
         return 1;
      }
   }
   else if (t == VARIABLETYPE) {
      strcpy(s, token);
      return 0;
   }
   else {
      printf("error, expected data type\n");
   }
   debug = 0;
   return 1;
}

int gettoken(void)  /* return next token */
{
   int c, getch(void);
   void ungetch(int);
   char *p = token;
   
   while ((c = getch()) == ' ' || c == '\t')
      ;
   if (c == '(') {
      if ((c = getch()) == ')') {
         strcpy(token, "()");
         return tokentype = PARENS;
      } else {
         ungetch(c);
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
      if (!strcmp(token, qualifiers[0]) || !strcmp(token, qualifiers[1]))
         return QUALIFIER;
      int i;
      for (i = 0; i < 9; ++i)
         if (!strcmp(token, types[i]))
            return VARIABLETYPE;
      return tokentype = NAME;
   } else
      return tokentype = c;
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
