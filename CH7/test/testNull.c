#include <stdio.h>
int main()
{
   char str[3] = "ab";
   char *c = str;
   printf("fuu\0511\n");    // only "fuu" will be printed
   printf("\100\n");
   printf("%c\n", (*c++ = 'c'));
   return 0;
}
