/*
 * how to initialize array of pointers?
 */

#include <stdio.h>
main()
{
   int a = 123, b = 456, c = -1;
   int *p[3] = {&a, &b};
   printf("*p[0] = %d\n", *p[0]);
   printf("p[2] = %d\n", (int) p[2]);
   p[2] = &c;
   printf("p[2] = %d\n", (int) p[2]);
   printf("*p[2] = %d\n", *p[2]);
   return 0;
}
