/*
 * Exercise 6-3: Write a cross-referencer that prints a list of all words in a
 * document, and, for each word, a list of the line numbers on which it occurs.
 * Remove noise words like "the," "and," and so on.
 *
 * My implementation does not deal with noise words.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

struct listNode {
   int line;
   struct listNode *next;
};

struct treeNode {
   struct listNode *lineList;
   char *word;
   struct treeNode *LChild, *RChild;
};

int getword(char *, int);
struct treeNode *addToTree(char *, struct treeNode *, int); // tree of variable
                                                           // declaration group
struct listNode *addToLineList(struct listNode *, int);
void printList(struct treeNode *);
int getch(void);
void ungetch(int);

main(int argc, char *argv[])
{
   int line = 1, c;
   char word[MAXWORD], nextWord[MAXWORD];
   
   struct treeNode *root = NULL;
   while ((c=getword(word, MAXWORD)) != EOF) {
      if (c == '\n')
         ++line;
      else
         root = addToTree(word, root, line);
   }
   printList(root);
   return 0;
}

/* getword:  get next word or character from input */
int getword(char *word, int lim)
{
   int c;
   char *w = word;
   
   while ((isspace(c = getch()) || !isalpha(c)) && c != '\n' && c != EOF)
      ;
   *w++ = c;
   if (c == EOF || c == '\n') {
      *w = '\0';
      return c;
   }
   for ( ; --lim > 0 && (isalnum(c = getch()) || c == '_'); w++)
      *w = c;
   ungetch(c);
   *w = '\0';
   return word[0];
}

char *Strdup(char *);

struct listNode *addToLineList(struct listNode *list, int line)
{
   struct listNode *start = list;
   if (list == NULL) {
      list = (struct listNode *) malloc(sizeof(struct listNode));
      list->line = line;
      list->next = NULL;
      return list;
   } else {
      while (list->next)
         list = list->next;
      list->next = (struct listNode *) malloc(sizeof(struct listNode));
      list->next->line = line;
      list->next->next = NULL;
      return start;
   }
}

struct treeNode *addToTree(char *newWord, struct treeNode *node, int line)
{
   char *s;
   if (node == NULL) {
      node = (struct treeNode *) malloc(sizeof(struct treeNode));
      node->word = Strdup(newWord);
      node->lineList = NULL;
      node->lineList = addToLineList(node->lineList, line);
      node->LChild = node->RChild = NULL;
   } else {
      s = node->word;
      if (strcmp(newWord, s) > 0)
         node->RChild = addToTree(newWord, node->RChild, line);
      else if (strcmp(newWord, s) < 0)
         node->LChild = addToTree(newWord, node->LChild, line);
      else
         node->lineList = addToLineList(node->lineList, line);
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

void printWord(struct listNode *list)
{
   while (list != NULL) {
      printf((list->next == NULL) ? "%d\n" : "%d, " , list->line);
      list = list->next;
   }
}

void printList(struct treeNode *root)
{
   if (root->LChild)
      printList(root->LChild);
   
   printf("%s\n\t", root->word);
   printWord(root->lineList);
   
   if (root->RChild)
      printList(root->RChild);
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
