/*
 * Exercise 4-12: Adapt the ideas of printd to write a recursive version of itoa
 * , that is, convert an integer into a string by calling a recursive routine.
 */

#include <stdio.h>
#include <string.h>

#define MAXLENGTH 100

void itoa(char [], int, int);
void reverse(char []);

main()
{
   int n = 12345;
   char a[100];
   itoa(a, n, 0);
   printf("%s\n" , a);
   return 0;
}

void itoa(char s[], int n, int last)
{
   if (n / 10)
      itoa(s, n / 10, last + 1);
   else
      s[last+1] = '\0';
   s[last] = n % 10 + '0';
   if (last == 0)
      reverse(s);
}

void reverse(char s[])
{
   int i, j, temp;
   for (i = 0, j = strlen(s)-1; i < j; ++i, --j) {
      temp = s[i];
      s[i] = s[j];
      s[j] = temp;
   }
}
