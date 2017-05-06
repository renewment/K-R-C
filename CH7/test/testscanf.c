#include <stdio.h>
#include <ctype.h>
int main()
{
   char c = 'g';
   int count, i = 0;
   while (scanf("%c", &c))
      if (c != ' ')
         printf("%c", c);
   return 0;
}
