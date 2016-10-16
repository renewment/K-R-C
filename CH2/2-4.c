/*
 * Write an alternate version of squeeze(s1,s2)
 * that deletes each character in s1 that matches
 * any character in the string s2.
 */
 
#include <stdio.h>
#define length 21

void squeeze(char s1[], char s2[]);

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
   
   squeeze(s1, s2);
   printf("new s1: %s\n", s1);
   return 0;
}

void squeeze(char s1[], char s2[])
{
   int i, j, current;
   
   for (i = current = 0; s1[i] != '\0'; ++i) {
      for (j = 0; s2[j] != '\0' && s1[i] != s2[j]; ++j)
         ;
      if (s2[j] == '\0')
         s1[current++] = s1[i];
   }
   s1[i] = '\0';
}
