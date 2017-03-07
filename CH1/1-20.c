/*
 * Exercise 1-20. Write a program deteb that replacces tabs in the input with
 * the proper number of blanks to space to the next tab stop. Assume a fixed set
 * of tab stops, say every N columns. Should N be a variable or a symbolic
 * parameter?
 */

#include <stdio.h>

#define N 8

main()
{
   int i, counter;
   char c;
   
   counter = N;
   
   while ((c = getchar()) != EOF) {
      if (c == '\t') {
         for (i = 0; i < counter; ++i)
            putchar(' ');
         counter = N;
      } else if (c == '\n') {
         counter = N;
         putchar(c);
      } else {
         putchar(c);
         --counter;
         if (counter == 0)
            counter = N;
      }
      
   }
   
   return 0;
}
