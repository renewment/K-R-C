/*
 * Write a program to "fold" long input lines into
 * two or more shorter lines after the last non-blank
 * character that occurs before the n-th column of
 * input. Make sure your program does something
 * intelligent with very long lines, and if there
 * are no blanks or tabs before the specified column.
 */

#include <stdio.h>

#define N 30   // 每一行的上限為30字元

main()
{
   int wordLength, space, front, rear;
   
   //buffer用來存讀入的
   char c, word[N], buffer[2*N];
   wordLength = front = rear = 0;
   space = N;
   while ((c = getchar()) != EOF) {
      if (c == '\n' || c == ' ') {
         //printf("wordLength: %d\nspace: %d\n", wordLength, space);
         if ((wordLength = rear - front) <= space) {
            buffer[rear] = '\0';
            printf("%s" , buffer);
            space = space - wordLength;
         } else {
            while ((wordLength = rear - front) > 0) {
               for (;space > 1 && (wordLength = rear - front) > 0; --space) {
                  putchar(buffer[front]);
                  ++front;
               }
               if (wordLength > 0) {
                  putchar('-');
                  putchar('\n');
                  space = N;
               }
            }
         }
         if (c == ' ' && space > 1) {
            putchar(c);
            --space;
         } else {
            putchar('\n');
            space = N;
         }
         front = rear = 0;
      } else {
         buffer[rear] = c;
         ++rear;
      }
   }
   return 0;
}
