/*
 * Exercise 2-1. Write a program to determine the ranges of char, short, int,
 * and long variables, both signed and unsigned, by printing appropriate values
 * from standard headers and by direct computation. Harder if you compute them:
 * determine the ranges of the various floating-point types.
 */

#include <stdio.h>
#include <float.h>
#include <limits.h>

main()
{
   char c;
   unsigned char uc;
   short s;
   unsigned short us;
   int i, ii;
   unsigned int ui;
   long l;
   unsigned long ul;
   float f, f_tmp;
   double d, d_tmp;
   c = uc = s = us = i = ui = l = ul = 0;
   f = f_tmp = d = d_tmp = 1;
   
   printf("\n");
   printf("from header:\n");
   printf("char min:           %d\n", CHAR_MIN);
   printf("char max:           %d\n", CHAR_MAX);
   printf("unsigned char max:  %d\n\n", UCHAR_MAX);
   printf("short min:          %d\n", SHRT_MIN);
   printf("short max:          %d\n", SHRT_MAX);
   printf("unsigned short max: %d\n\n", USHRT_MAX);
   printf("int min:            %d\n", INT_MIN);
   printf("int max:            %d\n", INT_MAX);
   printf("unsigned int max:   %u\n\n", UINT_MAX);
   printf("long min:           %ld\n", LONG_MIN);
   printf("long max:           %ld\n", LONG_MAX);
   printf("unsigned long max:  %lu\n\n", ULONG_MAX);
   
   printf("-----------------------------------------\n\n");
   
   printf("by computation:\n");
   
   for (ii=0; ii < 7; ++ii)
      c = c * 2 + 1;
   printf("char max:           %d\n", c);
   c = -c - 1;
   printf("char min:           %d\n", c);
   for (ii=0; ii < 8; ++ii)
      uc = uc * 2 + 1;
   printf("unsigned char max:  %u\n\n", uc);
   
   for (ii=0; ii < 15; ++ii)
      s = s * 2 + 1;
   printf("short max:          %d\n", s);
   s = -s - 1;
   printf("short min:          %d\n", s);
   for (ii=0; ii < 16; ++ii)
      us = us * 2 + 1;
   printf("unsigned short max: %u\n\n", us);
   
   for (ii=0; ii < 31; ++ii)
      i = i * 2 + 1;
   printf("int max:            %d\n", i);
   i = -i - 1;
   printf("int min:            %d\n", i);
   for (ii = 0; ii < 32; ++ii)
      ui = ui * 2 + 1;
   printf("unsigned int max:   %u\n\n", ui);
   
   for (ii = 0; ii < 63; ++ii)
      l = l * 2 + 1;
   printf("long max:           %ld\n", l);
   l = -l - 1;
   printf("long min:           %ld\n", l);
   for (ii=0; ii < 64; ++ii)
      ul = ul * 2 + 1;
   printf("unsigned long max:  %lu\n", ul);
   
   return 0;
}
