/*
 * Exercise 1-13. Write a program to print a histogram of the lengths of words
 * in its input. It is easy to draw the histogram with the bars horizontal; a
 * vertical orientation is more challenging.
 */

#include <stdio.h>

#define TRUE      1
#define FALSE     0
#define MAXLENGTH 15

main()
{
   int length[MAXLENGTH], i, j, counter, word, longest;
   char c;
   
   counter = 0;
   longest = 0;
   word = FALSE;
   for (i = 0; i < MAXLENGTH; ++i)
      length[i] = 0;
   
   while((c = getchar()) != EOF) {
      
      if (c == ' ' || c == '\t' || c == '\n')
         word = FALSE;
      else {
         word = TRUE;
         ++counter;
      }
      if (word == FALSE && counter != 0) {
         ++length[--counter];
         if (length[counter] > longest)
            longest = length[counter];
         counter = 0;
      }
   }
   
// print horizontal histogram
   for (i = 0; i < MAXLENGTH; ++i) {
      printf("%2d:" , i+1);
      for (j = 0; j < length[i]; ++j)
         putchar('*');
      putchar('\n');
   }
   putchar('\n');
   
// print vertical histogram
   for (i = longest; i >= 0; --i) {
      for (j = 0; j < MAXLENGTH; ++j)
         if (length[j] == longest && longest > 0) {
            printf(" * ");
            --length[j];
         } else {
            printf("   ");
         }
      --longest;
      putchar('\n');
   }
   for (i = 0; i < MAXLENGTH; ++i)
      printf("%2d ", i + 1);
   putchar('\n');
}
