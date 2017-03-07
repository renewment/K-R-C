/*
 * Exercise 5-4: Write the function strend(s,t), which returns 1 if the string t
 * occurs at the end of the string s, and zero otherwise.
 */

#include <stdio.h>
#include <string.h>

#define SIZE 100
int strend(char *s, char *t);

main()
{
   char s[SIZE] = "sdfdsf sdfs fsda fds asdfs sad sd656 5sd";
   char t[] = "ad sd656 5sd";
   printf("%d\n", strend(s, t));
   return 0;
}

int strend(char *s, char *t)
{
   if (strlen(s) < strlen(t))
      return 0;
   
   int i = strlen(t);
   s = s + strlen(s) - 1;
   t = t + strlen(t) - 1;
   for (; i > 0 && *s == *t; --i, --s, --t)
      ;
   return i == 0 ? 1 : 0;
}
