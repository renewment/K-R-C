/*
 * Exercise 2-6. Write a function setbits(x,p,n,y) that returns x with the n
 * bits that begin at position p set to the rightmost n bits of y, leaving the
 * other bits unchanged.
 */

#include <stdio.h>

#define MAXLENGTH 33

unsigned int setbits(unsigned int x, int p, int n, unsigned int y);

main()
{
   unsigned int x = 0b11111111111111111111111111111111;
   unsigned int y = 0b00000000000000000000000000000000;
   int p = 6;
   int n = 5;
   x = setbits(x, p, n, y);
   
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

unsigned int setbits(unsigned int x, int p, int n, unsigned int y)
{
   unsigned int target = (~((~0) << n)) & y; // keep the rightmost n bits in y
   target = target << p;                     // shift target bits to the
                                             // designated position
   printf("target: %u\n" , target);
   
   unsigned int mask = (~((~0) << n)) << (p - n);
   mask = ~mask;
   return (x & mask) | target;
}
