/*
 * Write a function expand(s1,s2) that expands shorthand notations like a-z in
 * the string s1 into the equivalent complete list abc...xyz in s2 . Allow for
 * letters of either case and digits, and be prepared to handle cases like a-b-c
 * and a-z0-9 and -a-z . Arrange that a leading or trailing - is taken literally
 * .
 */

void expand(char s1[], char s2[]);
#define MAXLENGTH 1000
#include <stdio.h>

main()
{
   char s1[MAXLENGTH] = "-1-8A-GG-Z-";
   char s2[MAXLENGTH];
   printf("s1: %s\n" , s1);
   expand(s1, s2);
   printf("s2: %s\n" , s2);
   
   return 0;
}

void expand(char s1[], char s2 [])
{
   int i, j, hyphen, flag, counter;
   char startC, endC;
   hyphen = counter = 0;
   startC = endC = (char) 0;
   for (i = 0, flag = 0; s1[i] != '\0' && i < MAXLENGTH - 1; ++i) {
      if (s1[i] != '-') {
         if (hyphen)
            endC = s1[i];
         else {
            startC = s1[i];
            s2[counter++] = startC;
         }
      }
      else {
         if (startC != 0)
            hyphen = 1;
         else
            s2[counter++] = s1[i];
      }
      if (endC) {
         for (j = startC + 1; j <= endC; ++j)
            s2[counter++] = (char) j;
         hyphen = 0;
         startC = endC;
         endC = (char) 0;
      }
   }
   if (hyphen)
      s2[counter++] = '-';
   s2[counter] = '\0';
   return;
}
