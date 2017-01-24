/*
 * Exercise 2-10. Rewrite the function lower, which converts upper case letters
 * to lower case, with a conditional expression instead of if-else.
 */

int lower(int c);

#include <stdio.h>

main()
{
   char c;
   
   while((c = getchar()) != EOF)
      printf("%c" , (char) lower((int) c));
   printf("\n");
   
   return 0;
}

int lower(int c)
{
   return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}
