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

struct listNode {
   char *var;
   struct listNode *next;
};

struct treeNode {
   struct listNode *vars;
   struct treeNode *LChild, *RChild;
};
char *keywords[] = {"char", "const", "define", "do", "double", "else", "enum",
                    "float", "for", "goto", "if", "int", "long", "main",
                    "register", "return", "short", "signed", "struct",
                    "unsigned", "void", "while"};
#define NKEYWORDS (sizeof(keywords) / sizeof(keywords[0]))

int getword(char *, int);
int binsearch(char *, char *[], int);
struct treeNode *addToTree(char *, struct treeNode *, int);  // tree of variable
struct listNode *addToGroup(char *, struct listNode *);   // save variable group
                                                            // declaration group
int getch(void);
void ungetch(int);
void printVar(struct treeNode *);
/* count C keywords */
main(int argc, char *argv[])
{
   int n = N;
   char word[MAXWORD];
   
   if (argc > 2) {                  // parse parameter
      printf("error, too many arguments\n");
      return -1;
   }
   if (argc == 2)
      n = atoi(argv[1]);
   
   int c;
   struct treeNode *root = NULL;
   while ((c=getword(word, MAXWORD)) != EOF)
      if (c == '_' || isalpha(c))
         if (binsearch(word, keywords, NKEYWORDS) < 0)
            root = addToTree(word, root, n);
   
   printVar(root);
   return 0;
}

/* getword:  get next word or character from input */
int getword(char *word, int lim)
{
   int c, previousC, nextC, escape, asterisk;
   char *w = word;
   escape = asterisk = 0;
   
   while (isspace(c = getch()))
      ;
   *w++ = c;
   if (!isalpha(c) && // check alpha
       c != '_' &&    // check underscore
       c != '\'' &&   // check char
       c != '\"' &&   // check string constant
       c != '/' &&    // check start of line or block comment
       c != '#') {    // check preprocessor control
      *w = '\0';
      return c;
   }
   if (c == '\'') {              // parse single character
      if ((c=getch()) == '\\')
         c = getch();
      c = getch();
      *w = '\0';
      return '\'';
   }
   if (c == '\"') {       // parse string
      previousC = c;
      while ((c=getch()) != EOF) {
         if (c == '\\' && !escape)
            escape = 1;
         else if (escape)
            escape = 0;
         else if (c == '\"')
            break;
      }
      *w = '\0';
      return '\"';
   }
   if (c == '/') {
      if ((nextC=getch()) == '/') {         // line comment
         while ((c=getch()) != EOF)
            if (c == '\n')
               break;
      } else if (nextC == '*')              // block comment
         while ((c=getch()) != EOF)
            if (c == '*')
               asterisk = 1;
            else if (c == '/' && asterisk)
               break;
            else
               asterisk = 0;
      else                                  // slash for division
         ungetch(nextC);
      *w = '\0';
      return '/';
   }
   if (c == '#') {
      while ((c=getch()) != EOF)
         if (c == '\n')
            break;
      *w = '\0';
      return '#';
   }
   for ( ; --lim > 0; w++)
      if (!isalnum(*w = getch()) &&       // check alpha or number
         *w != '_') {                     // check underscore
         ungetch(*w);
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

struct listNode *addToGroup(char *s, struct listNode *list)
{
   struct listNode *start = list;
   struct listNode *previous = NULL;
   if (list == NULL) {
      list = (struct listNode *) malloc(sizeof(struct listNode));
      list->var = Strdup(s);
      list->next = NULL;
      return list;
   } else {
      while (list->next && strcmp(s, list->var) > 0) {
         previous = list;
         list = list->next;
      }
      if (strcmp(s, list->var) == 0)
         return start;
      struct listNode *temp =
         (struct listNode *) malloc(sizeof(struct listNode));
      temp->var = Strdup(s);
      if (strcmp(s, list->var) > 0) {
         temp->next = list->next;
         list->next = temp;
      } else {
         temp->next = list;
         if (previous)
            previous->next = temp;
         else
            start = temp;
      }
      return start;
   }
}

char *Strdup(char *s)   /* make a duplicate of s */
{
   char *p;
   p = (char *) malloc(strlen(s)+1);   /* +1 for '\0' */
   if (p != NULL)
      strcpy(p, s);
   return p;
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
