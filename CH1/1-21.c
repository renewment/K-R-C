/*
 * Exercise 1-21. Write a program entab that replaces strings of blanks by the
 * minimum number of tabs and blanks to achieve the same spacing. Use the same
 * tab stops as for detab. When either a tab or single blank would suffice to
 * reach a tab stop, which should be given preferenc?
 */

#include <stdio.h>

#define N 8

main()
{
   int counter, position;
   char c;
   
   position = N;
   counter = 0;
   while((c = getchar()) != EOF) {
      if (c == '\n') {
         while (counter > 0) {
            putchar(' ');
            --counter;
         }
         putchar(c);
         position = N;
      }
      else if (c == ' ') {
         ++counter;
         if (position - counter == 0) {
            //putchar('\t');
               while(position > 0) {
                     putchar('~');
                  --position;
               }
            //
            counter = 0;
            position = N;
         }
      }
      else if (c == '\t') {
         //putchar(c);
            while(position > 0) {
               putchar('~');
               --position;
            }
         //
         counter = 0;
         position = N;
      }
      else {
         while (counter > 0) {
            putchar(' ');
            --counter;
            --position;
         }
         putchar(c);
         --position;
      }
   }
   return 0;
}
