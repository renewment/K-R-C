/*
 * Exercise 2-9. In a two's complement number system, x &= (x-1) deletes the
 * rightmost 1-bit in x . Explain why. Use this observation to write a faster
 * version of bitcount.
 */

#include <stdio.h>

int bitcount(unsigned x);

main()
{
   unsigned x = 0b10010110011010011111000101001001;
   int count = bitcount(x);
   
   printf("1-bits in x: %d\n" , count);
   
   return 0;
}

int bitcount(unsigned x)
{
   int b;
   for (b = 0; x != 0; x &= x-1)
      ++b;
   
   return b;
}
