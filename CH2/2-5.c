/*
 * Exercise 2-5. Write the function any(s1,s2), which returns the first location
 * in the string s1 where any character from the string s2 occurs, of -1 if s1
 * contains no characters from s2. (The standard library function strpbrk does
 * the same job but returns a pointer to the location.)
 */

#include <stdio.h>
#define length 30

int any(char s1[], char s2[]);

main()
{
   char s1[length], s2[length];
   char c;
   int counter;
   
   printf("s1: ");
   counter = 0;
   while ((c=getchar()) != '\n' && counter < length - 1)
      s1[counter++] = c;
   s1[counter] = '\0';
   
   printf("s2: ");
   counter = 0;
   while ((c=getchar()) != '\n' && counter < length - 1)
      s2[counter++] = c;
   s2[counter] = '\0';
   
   printf("location is %d\n", any(s1, s2));
   return 0;
}

int any(char s1[], char s2[])
{
   int i, j, location;
   location = -1;
   for (i = 0; s1[i] != '\0' && location == -1; ++i) {
      for (j = 0; s2[j] != '\0' && s1[i] != s2[j]; ++j)
         ;
      if (s2[j] != '\0')
         location = i;
   }
   return i;
}
