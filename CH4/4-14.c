/*
 * Exercise 4-14: Define a macro swap(t,x,y) that interchanges two arguments of
 * type t. (Block structure will help).
 */

#include <stdio.h>
#define swap(t,x,y)  if (1) { \
                        t temp = x;\
                        x = y;\
                        y = temp;\
                     }

main()
{
   int i = 5;
   int j = 10;
   swap(int, i, j);
   printf("i = %d, j = %d\n", i, j);
   return 0;
}
