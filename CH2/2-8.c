/*
 * Exercise 2-8. Write a function rightrot(x,n) that returns the value of the
 * integer x rotated to the right by n bit positions.
 */

#include <stdio.h>

#define MAXLENGTH 33

unsigned int rightrot(unsigned int x, int n);

main()
{
   unsigned x = 0b00000000000000001111111100010101;
   int n = 5;
   x = rightrot(x, n);
   
   char pattern[MAXLENGTH];
   int length = 0;
   int counter;
   for (counter = 31; counter >= 0; --counter) {
      if ((x & 1) == 1)
         pattern[counter] = '1';
      else
         pattern[counter] = '0';
      x = x >> 1;
   }
   pattern[MAXLENGTH-1] = '\0';
   printf("result: %s\n" , pattern);
   return 0;
}

unsigned int rightrot(unsigned int x, int n)
{
   unsigned int MSB0 = 0x7FFFFFFF;
   unsigned int MSB1 = 0x80000000;
   
   for (; n > 0; --n)
      if ((x & 1) == 1)
         x = (x >> 1) | MSB1;
      else
         x = (x >> 1) & MSB0;
   
   return x;
}
