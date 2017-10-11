#include <stdio.h>
int main()
{
   printf("%d\n", (020 & (01|010|020)) != 01);
   return 0;
}
