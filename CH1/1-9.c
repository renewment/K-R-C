/*
 * Write a program to copy its input to its output,
 * replacing each string of one or more blanks by a single blank.
 */

#include <stdio.h>
main()
{
   char c;
   int blankCounter;
   blankCounter = 0;
   while ((c = getchar()) != EOF) {
      if (blankCounter == 0)
         putchar(c);
      if (c == ' ')
         ++blankCounter;
      if (c != ' ')
         blankCounter = 0;
   }
}