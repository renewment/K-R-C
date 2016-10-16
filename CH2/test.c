#include <stdio.h>
#include <math.h>
main()
{
   int n = 1;
   printf("%lf" , sqrt(n));
   return 0;
   int a = 0x7fffffff;
   float f = a;
	printf("a = %d\n" , a);
   printf("f = %f\n" , f);
   
   a = 0x7ffffff0;
   f = (float) a;
   printf("a = %d\n" , a);
   printf("f = %f\n" , f);
	return 0;
}
