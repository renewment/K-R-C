/*
 * Exercise 8-6: The standard library function calloc(n,size) returns a pointer
 * to n objects of size size, with the storage initialized to zero. Write calloc
 * , by calling malloc or by modifying it.
 */

#include <stdio.h>
#include <stdlib.h>

void *calloc(size_t, size_t);

void *calloc(size_t n, size_t size)
{
   char *ptr = malloc(n * size);
   int i;
   
   for (i = 0; i <= n*size; ++i)
      *(ptr+i) = (char) 0;
   
   return (void*) ptr;
}

main()
{
   int n = 10, i;
   int *intA = calloc(n, sizeof(int));
   for (i = 0; i < n;)
      printf("%d\n", *(intA + i++));
   
   return 0;
}
