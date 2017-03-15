#include <stdio.h>
#define dprint(expr) printf("%s1\n", expr)
main()
{
   dprint("\n");
   char fuu[10];
   printf("fuu[0]: %d\n", fuu[0]);
   return 0;
}

