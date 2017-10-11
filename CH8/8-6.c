/*
 * Exercise 8-6: The standard library function calloc(n,size) returns a pointer
 * to n objects of size size, with the storage initialized to zero. Write calloc
 * , by calling malloc or by modifying it.
 */

#include <stdio.h>
#include <stdlib.h>

void *calloc(size_t, size_t);
