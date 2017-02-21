/*
 * Exercise 4-13: Write a recursive version of the function reverse(s), which
 * reverse the string s in place.
 */

#include <stdio.h>
#include <string.h>

#define MAXLENGTH 100

void reverse(char [], int, int);

main()
{
   char s[] = "abcdefg";
   reverse(s, 0, strlen(s)-1);
   printf("%s\n", s);
   return 0;
}

void reverse(char s[], int left, int right)
{
   int temp;
   if (left < right)
      reverse(s, left+1, right-1);
   temp = s[left];
   s[left] = s[right];
   s[right] = temp;
}
