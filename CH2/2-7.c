/*
 * Exercise 2-7. Write a function invert(x,p,n) that returns x with the n bits
 * that begin at position p inverted (i.e., 1 changed into 0 and vice versa),
 * leaving the others unchanged.
 */

#include <stdio.h>

#define MAXLENGTH 33

unsigned int invert(unsigned int x, int p, int n);

main()
{
   unsigned int x = 0b11111111111111111111100101011011;
   int p = 6;
   int n = 5;
   x = invert(x, p, n);
   
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

unsigned int invert(unsigned int x, int p, int n)
{
   unsigned int mask = 0;
   p = p - n;
   for (;n > 0; --n)
      mask = (mask << 1) + 1;
   for (; p > 0; --p)
      mask = mask << 1;
   return x ^ mask;
}
