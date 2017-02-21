/*
 * Exercise 4-9: Our getch and ungetch do not handle a pushed-back EOF correctly
 * . Decide what their properties ought to be if an EOF is pushed back, then
 * implement your design.
 */

#include <stdio.h>
#include <stdlib.h>   /* for atof() */

#define BUFSIZE 100
char buf[BUFSIZE];
int front = 0;
int rear = 0;

int getch(void);
void ungetch(int);

main()
{
   char s[MAXOP];
   
   return 0;
}

// structure of buf should be queue (FIFO) rather than stack (FILO)
int getch(void) /* get a (possibly pushed back) character */
{
   int value;
   if (front != rear) {
      value = buf[front];
      front = (front+1) % BUFSIZE;
      return value;
   }
   else
      return getchar();
}

void ungetch(int c) /* push character back on input */
{
   if (((rear+1) % BUFSIZE) == front)
      printf("ungetch: too many characters\n");
   else {
      buf[rear] = c;
      rear = (rear+1) % BUFSIZE;
   }
}
