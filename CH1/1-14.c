/*
 * Exercise 1-14. Write a program to print a histogam of the frequencies of
 * different characters in its input.
 */

#include <stdio.h>

#define NUMOFCHAR 26

main()
{
   int characters[NUMOFCHAR], i, j;
   char c;
   
   for (i = 0; i < NUMOFCHAR; ++i)
      characters[i] = 0;
   
   while((c = getchar()) != EOF) {
      if (c >= 'a' && c <= 'z')
         ++characters[c - 'a'];
   }
   
   for (i = 0; i < NUMOFCHAR; ++i) {
      printf("%c:" , i + 'a');
      for (j = 0; j < characters[i]; ++j)
         putchar('*');
      putchar('\n');
   }
   putchar('\n');
}
