/*
 * Exercise 1-8. Write a program to count blanks, tabs, and newlines.
 */

#include <stdio.h>

main()
{
   long nb;
   char c;
   nb = 0;
   
   while((c = getchar()) != EOF) {
      if (c == ' ')
         ++nb;
      if (c == '\t')
         ++nb;
      if (c == '\n')
         ++nb;
   }
   
   printf("# of blanks, tabs and newlines are %ld\n" , nb);
}
