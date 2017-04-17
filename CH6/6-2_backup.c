/*
 * Exercise 6-2: Write a program that reads a C program and prints in
 * alphabetical order each group of variable names that are identical in the
 * first 6 characters, but different somewhere thereafter. Don't count words
 * within strings and comments. Make 6 a parameter that can be set from the
 * command line.
 *
 * I use the code of exercise 5-20 for parsing variable names and functions.
 *
 * TODO:
 * modify function codes in {}
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define N 6                // default length of identical string
enum status {CONTEXT, LINECOMMENT, BLOCKCOMMENT, PREPROC, ENUM, FUNC};

struct listNode {
   char *var;
   struct listNode *next;
};

struct treeNode {
   struct listNode *vars;
   struct treeNode *LChild, *RChild;
};
char *types[] = {"char", "double", "float",
                 "int", "long", "short",
                 "signed", "unsigned", "void"};
char *qualifiers[] = {"const", "volatile"};
#define NTYPES (sizeof(types) / sizeof(types[0]))

int getword(char *, int);
int binsearch(char *, char *[], int);
struct listNode *addToGroup(char *, struct listNode *);   // save variable group
struct treeNode *addToTree(char *, struct treeNode *, int);  // tree of variable
struct treeNode *parseES(struct treeNode *, char *, int); // parse enum & struct
struct treeNode *parseDeclaration(struct treeNode *, char *, int);// parse
                                                            // declaration group
int getch(void);
void ungetch(int);
void printVar(struct treeNode *);
int fuu = 0;
/* count C keywords */
int main(int argc, char *argv[])
{
   int n = N, nextC;
   char word[MAXWORD], nextWord[MAXWORD];
   if (argc > 2) {
      printf("error, too many arguments\n");
      return -1;
   }
   if (argc == 2)
      n = atoi(argv[1]);
   
   int c, first = 1, isVariable = 0, declaration = 0;
   struct treeNode *root = NULL;
   enum status s = CONTEXT;
   while ((c=getword(word, MAXWORD)) != EOF) {
      if (strncmp(word, "//", 2) == 0) {
         s = LINECOMMENT;
         first = 0;
      } else if (strncmp(word, "/*", 2) == 0) {
         s = BLOCKCOMMENT;
         first = 0;
      }
      if (first) {
         if (word[0] == '#')
            s = PREPROC;
         else
            s = CONTEXT;
         first = 0;
         if (strcmp(word, "enum") == 0 || strcmp(word, "struct") == 0)
            root = parseES(root, word, n);
         else if (binsearch(word, types, NTYPES) >= 0)
            root = parseDeclaration(root, word, n);
      }
      if (s == LINECOMMENT || s == PREPROC) {
         if (word[0] == '\n') {
            s = CONTEXT;
            first = 1;
         }
         continue;
      } else if (s == BLOCKCOMMENT) {
         int len = strlen(word);
         if (strcmp(&word[len-2], "*/") == 0)
            s = CONTEXT;
         continue;
      }
      if (s == CONTEXT && word[0] == '\n')
         first = 1;
   }
   
   printVar(root);
   return 0;
}

/* getword:  get next word or character from input */
int getword(char *word, int lim)
{
   int c, nextC, isString;
   char *w = word;
   isString = 0;
   
   while (isspace(c = getch()) && c != '\n')
      ;
   if (c == '\n') {
      *w++ = '\n';
      *w = '\0';
      return c;
   }
   if (c != EOF)
      *w++ = c;
   if (!isalpha(c) && // check alpha
       c != '_' &&    // check underscore
       c != '\"' &&   // check string constant
       c != '/' &&    // check start of line or block comment
       c != '*' &&    // check end of block comment
       c != '#') {    // check preprocessor control
      *w = '\0';
      return c;
   }
   if (c == '\"')
      isString = 1;
   if (c == '/') {
      if ((nextC=getch()) == '/') {       // if this word is //....//
         *w++ = nextC;
         while ((c=getch()) == '/')
            *w++ = c;
         ungetch(c);
         *w = '\0';
      } else if (nextC == '*') {          // if this word is started by /*
         *w++ = nextC;
         while ((c=getch()) == '*')       // when there are consequent *
            *w++ = c;
         if (w - word > 2 && c == '/')    // if w record more than 3 char,
            *w++ = c;                     // i.e. w = "/*...*" and the last c is
         *w = '0';                        // '/', so this word will be /*...*/
      } else
         ungetch(nextC);                  // slash for division
      return word[0];
   }
   if (c == '*') {
      if ((nextC=getch()) == '/') {       // w is */
         *w++ = nextC;
      } else
         ungetch(nextC);
      *w = '\0';
      return word[0];
   }
   for ( ; --lim > 0; w++) {
      if (!isalnum(*w = getch()) &&       // check alpha or number
          *w != '_' &&           // check underscore
          *w != '\"') {          // check string constant
         ungetch(*w);
         break;
      }
      if (*w == '\"')                     // end of strint constant is read
         break;
   }
   *w = '\0';
   return word[0];
}

int binsearch(char *s, char *t[], int n)
{
   int cond;
   int low, high, mid;
   
   low = 0;
   high = n-1;
   while (low <= high) {
      mid = (low + high) / 2;
      if ((cond=strcmp(s, t[mid])) > 0)
         low = mid + 1;
      else if (cond < 0)
         high = mid - 1;
      else
         return mid;
   }
   return -1;
}
char *Strdup(char *);

struct listNode *addToGroup(char *s, struct listNode *list)
{
   struct listNode *start = list;
   if (list == NULL) {
      list = (struct listNode *) malloc(sizeof(struct listNode));
      list->var = Strdup(s);
      list->next = NULL;
      return list;
   } else {
      while (list->next && strcmp(s, list->next->var) > 0) {
         list = list->next;
      }
      if (strcmp(s, list->var) == 0)
         return start;
      struct listNode *temp =
      (struct listNode *) malloc(sizeof(struct listNode));
      temp->var = Strdup(s);
      temp->next = list->next;
      list->next = temp;
      return start;
   }
}

struct treeNode *addToTree(char *newVar, struct treeNode *node, int n)
{
   char *s;
   if (node == NULL) {
      node = (struct treeNode *) malloc(sizeof(struct treeNode));
      node->vars = NULL;
      node->vars = addToGroup(newVar, node->vars);
      node->LChild = node->RChild = NULL;
   } else {
      s = node->vars->var;
      if (strncmp(newVar, s, n) > 0)
         node->RChild = addToTree(newVar, node->RChild, n);
      else if (strncmp(newVar, s, n) < 0)
         node->LChild = addToTree(newVar, node->LChild, n);
      else
         node->vars = addToGroup(newVar, node->vars);
   }
   return node;
}

char *Strdup(char *s)   /* make a duplicate of s */
{
   char *p;
   p = (char *) malloc(strlen(s)+1);   /* +1 for '\0' */
   if (p != NULL)
      strcpy(p, s);
   return p;
}

/*
 * legal enumeration syntaxes:
 *
 *    ENUM :=  enum/struct Name {...} vars;
 *             enum/struct Name vars;
 *             enum/struct Name;
 *             enum/struct {...} vars;
 *             enum/struct {...};
 */
struct treeNode *parseES(struct treeNode *root, char *word, int n)
{
   int c = getword(word, MAXWORD), newV;
   if (c == '{') {      // parse {...} then check whether there is any var
   parseBrace:
      while ((c=getword(word, MAXWORD)) != '}')
         ;
   parseVar:               // parse variable names
      newV = 1;
      while ((c=getword(word, MAXWORD) != ';')) {
         if ((isalpha(c) || c == '_') && newV) {
            root = addToTree(word, root, n);
            newV = 0;
         } else if (c == ',')
            newV = 1;
      }
   } else {             // eName follows enum
      if ((c=getword(word, MAXWORD)) == '{')    // parse {...}
         goto parseBrace;
      else if (c != ';')                        // parse vars.
         goto parseVar;
      else                                      // rest case is "enum eName;"
         ;                                      // so do nothing
   }
   return root;
}

enum { NAME, PARENS, BRACKETS, QUALIFIER, VARIABLETYPE, STRUCTTYPE };
struct treeNode *dcl(struct treeNode *, char *, int);
struct treeNode *dirdcl(struct treeNode *, char *, int);
int  gettoken(void);
int  tokentype;           /* type of last token */
char token[MAXWORD];      /* last token string */
char datatype[MAXWORD];   /* data type = char, int, etc. */
char out[1000];           /* output string */
struct treeNode *args(struct treeNode *, char *, int);
int debug = 0;
int parseArg = 0;

struct treeNode *parseDeclaration(struct treeNode *root, char *word, int n)
{
   int c;
   do {
      root = dcl(root, word, n);
      if (tokentype == '=') {
         gettoken();
         if (tokentype == '{')            // there would be problem if initiaize
            while (tokentype != '}')      // 2-D or high dimensional array
               gettoken();
         while (tokentype != ',' && tokentype != ';')
            gettoken();
      }
   } while (tokentype != ';');
   
   return root;
}

/* dcl:  parse a declarator */
struct treeNode *dcl(struct treeNode *root, char *word, int n)
{
   while (gettoken() == '*')   /* count *'s */
      ;
   root = dirdcl(root, word, n);
   return root;
}

/* dirdcl:  parse a direct declarator */
struct treeNode *dirdcl(struct treeNode *root, char *word, int n)
{
   int type;
   
   if (tokentype == '(') {        /* ( dcl ) */
      root = dcl(root, word,  n);
      if (tokentype != ')') {
         printf("error: missing )\n");
         return root;
      }
   } else if (tokentype == NAME && !parseArg) {  /* variable name */
      strcpy(word, token);                      // not needed?
      root = addToTree(token, root, n);
   } else if (tokentype == NAME)                 /* argument name */
      ;
   else if (tokentype == PARENS && parseArg)
      strcat(out, " function returning");
   else if (tokentype == BRACKETS && parseArg) {
      strcat(out, " array");
      strcat(out, token);
      strcat(out, " of");
   } else if (tokentype == ')' || tokentype == ',') {
      return root;
   } else {
      printf("token: %s\n", token);
      printf("error: expected name or (dcl)\n");
      return root;
   }
   while ((type=gettoken()) == PARENS || type == BRACKETS || type == '(') {
      if (type == PARENS)
         ;
      else if (type == BRACKETS) {
         strcat(out, " array");
         strcat(out, token);
         strcat(out, " of");
      } else {                   /* deel with arguments of function */
         strcat(out, " function, taking");
         root = args(root, word, n);
         if (tokentype != ')') {
            printf("error: missing )\n");
            return root;
         }
         if ((type=gettoken()) == '{')
         strcat(out, " as argument, returning");
      }
   }
   return root;
}

int parseType(char *);

/* args:  parse function arguments */
struct treeNode *args(struct treeNode *root, char *word, int n)
{
   int t;
   char argType[50] = "";
   while (!parseType(argType)) {                   /* variable type */
      parseArg = 1;
      root = dcl(root, word, n);
      parseArg = 0;
      strcat(out, " ");
      strcat(out, argType);
      if (tokentype == ')')
         break;
   }
   return root;
}

int parseType(char *s)
{
   int t;
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
   } else if (t == VARIABLETYPE) {
      strcpy(s, token);
      return 0;
   } else if (t == STRUCTTYPE) {
      gettoken();                         // parse struct name
      return 0;
   } else
      printf("error, expected data type\n");
   return 1;
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
      if (!strcmp(token, "struct"))
         return STRUCTTYPE;
      return tokentype = NAME;
   } else
      return tokentype = c;
}

void printList(struct listNode *);

void printVar(struct treeNode *root)
{
   if (!root) {
      printf("NULL\n");
      return;
   }
   if (root->LChild)
      printVar(root->LChild);
   printList(root->vars);
   printf("\n");
   if (root->RChild)
      printVar(root->RChild);
}

void printList(struct listNode *list)
{
   while (list) {
      printf("%s\n", list->var);
      list = list->next;
   }
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
