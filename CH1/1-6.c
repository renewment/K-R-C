#include <stdio.h>

main()
{
   int c;
   
   c = getchar() != EOF;
   printf("EOF = %d\n" , c);
}