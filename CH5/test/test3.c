#include <stdio.h>

void foo(int []);
int main()
{
   int fuu[] = {1, 2, 3, 4};
   foo(fuu);
   ++fuu;
   printf("%d\n", fuu[0]);
   return 0;
}

void foo(int fuu[])
{
   ++fuu;
   printf("%d\n", fuu[0]);
}
