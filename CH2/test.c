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
   
   unsigned int ui;
   ui = 1 << 1;
   printf("ui << 1 : %u\n" , ui);
   
   ui = 3 + -(-1); // !!!
   printf("u = %u\n" , ui);
	return 0;
}
