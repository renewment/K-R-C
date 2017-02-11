/*
 * In a two's complement number representation, our version of itoa does not
 * handle the largest negative number, that is, the value of n equal to
 * -(2^wordsize-1). Explain why not. Modify it to print that value correctly,
 * regardless of the machine on which it runs.
 */

#include <stdio.h>
#include <string.h>

#define MAXLENGTH 50

void reverse(char s[]);
void itoa(int n, char s[]);

main()
{
   int n = 0x80000000;
   char s[MAXLENGTH];
   itoa(n , s);
   printf("n = %s\n" , s);
   
   return 0;
}

/* reverse:  reverse string s in place */
void reverse(char s[])
{
   int c, i, j;
   
   for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
      c = s[i];
      s[i] = s[j];
      s[j] = c;
   }
}

/* itoa:  convert n to characters n s */
void itoa(int n, char s[])
{
   int i, sign, exception;
   
   if ((sign = n) < 0)
      n = -n;
   exception = n == -n ? 1 : 0;
   i = 0;
   do
      s[i++] = exception ? -(n % 10) + '0' : (n % 10) + '0';
   while ((n /= 10) != 0);
   
   if (sign < 0)
      s[i++] = '-';
   s[i] = '\0';
   reverse(s);
}
