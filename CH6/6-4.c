/*
 * Exercise 6-4: Write a program that prints the distinct words in its input
 * sorted into decreasing order of frequency of occurrence. Precede each word by
 * its count.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

struct treeNode {
   int count;
   char *word;
   struct treeNode *LChild, *RChild;
};
struct listNode {
   int count;
   char *word;
};

int getword(char *, int);
struct treeNode *addToTree(char *, struct treeNode *, int *);// tree of variable
                                                            // declaration group
void treeToList(struct treeNode *, struct listNode **);
void quickSort(struct listNode **, int, int);
void printList(struct listNode **, int);
int getch(void);
void ungetch(int);

main(int argc, char *argv[])
{
   int line = 1, c, length = 0;
   char word[MAXWORD], nextWord[MAXWORD];
   
   struct treeNode *root = NULL;
   // read inputs
   while ((c=getword(word, MAXWORD)) != EOF)
      root = addToTree(word, root, &length);
   // sort according frequency
   struct listNode **list =
         (struct listNode **) malloc(sizeof(struct listNode *) * length);
   treeToList(root, list);
   //printList(list, length);
   //printf("\n\n");
   quickSort(list, 0, length-1);
   // print
   printList(list, length);
   return 0;
}

/* getword:  get next word or character from input */
int getword(char *word, int lim)
{
   int c, nextC, isString;
   char *w = word;
   isString = 0;
   
   while ((isspace(c = getch()) || !isalpha(c)) && c != EOF)
      ;
   *w++ = c;
   if (c == EOF) {
      *w = '\0';
      return c;
   }
   for ( ; --lim > 0 && (isalnum(c = getch()) || c == '_'); w++)
      *w = c;
   ungetch(c);
   *w = '\0';
   return word[0];
}

char *Strdup(char *s)   /* make a duplicate of s */
{
   char *p;
   p = (char *) malloc(strlen(s)+1);   /* +1 for '\0' */
   if (p != NULL)
      strcpy(p, s);
   return p;
}

struct treeNode *addToTree(char *newWord, struct treeNode *node, int *length)
{
   char *s;
   if (node == NULL) {
      node = (struct treeNode *) malloc(sizeof(struct treeNode));
      node->count = 1;
      node->word = Strdup(newWord);
      node->LChild = node->RChild = NULL;
      ++*length;
   } else {
      s = node->word;
      if (strcmp(newWord, s) > 0)
         node->RChild = addToTree(newWord, node->RChild, length);
      else if (strcmp(newWord, s) < 0)
         node->LChild = addToTree(newWord, node->LChild, length);
      else
         ++node->count;
   }
   return node;
}

struct treeNode *popTreeNode(struct treeNode *);

void treeToList(struct treeNode *root, struct listNode ** list)
{
   struct treeNode *tn;
   while (root->count) {
      tn = popTreeNode(root);
      *list = (struct listNode *) malloc(sizeof(struct listNode));
      (*list)->word = Strdup(tn->word);
      (*list)->count = tn->count;
      list++;
      tn->count = 0;
   }
}

void quickSort(struct listNode ** list, int start, int end)
{
   struct listNode *temp;
   int mid = (start+end) / 2, last = start, i = start + 1;
   if (start >= end)
      return;
   //printf("mid: %d, start: %d, end: %d, last: %d\n", mid, start, end, last);
   // move pivot to the head of array
   temp = *(list + start);
   *(list + start) = *(list + mid);
   *(list + mid) = temp;
   while (i <= end) {
      if ((*(list+i))->count >= (*(list+start))->count) {
         temp = *(list + ++last);
         *(list+last) = *(list+i);
         *(list+i) = temp;
      }
      ++i;
   }
   // move pivot to the center
   temp = *(list+start);
   *(list+start) = *(list+last);
   *(list+last) = temp;
   //printList(list, 3);
   
   // sort former and later sub-array
   quickSort(list, start, last - 1);
   //printf("start: %d, last: %d, end: %d\n", start, last, end);
   quickSort(list, last + 1, end);
   return;
}

/* pop a tree node which has non-zero count */
struct treeNode *popTreeNode(struct treeNode *node)
{
   if (node->LChild && node->LChild->count)
      return popTreeNode(node->LChild);
   else if (node->RChild && node->RChild->count)
      return popTreeNode(node->RChild);
   else
      return node;
}

void printList(struct listNode **list, int length)
{
   while (length--) {
      printf("%d, %s\n", (*list)->count, (*list)->word);
      list++;
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
