/*
 * It's seems that strcmp converts all characters of parameters into unsigned
 * char
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
   char a[] = "12.34",
        b[] = "87, 89";
   printf("atof(a) : %lf\n", atof(a));
   printf("atof(b) : %lf\n", atof(b));
   return 0;
}
