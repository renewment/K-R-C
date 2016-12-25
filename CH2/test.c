#include <stdio.h>
#include <math.h>
main()
{
   int n = 1;
   printf("%lf" , sqrt(n));
   int a = 0x7fffffff;
   float f = a;
	printf("a = %d\n" , a);
   printf("f = %f\n" , f);
   
   a = 0x7ffffff0;
   f = (float) a;
   printf("a = %d\n" , a);
   printf("f = %f\n" , f);
   
   unsigned int ui = 0b111;
   printf("unsigned int ui: %u\n" , ui);
   printf("ui >> -2: %u\n" , ui >> (-2));
	return 0;
}
