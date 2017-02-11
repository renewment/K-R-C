/*
 * Exercise 3-5: Write the function itob(n, s, b) that converts the integer n
 * into a base b character representation in the string s. In particular,
 * itob(n, s, 16) formats n as a hexadecimal integer in s.
 */

void reverse(char s[]);
void itob(int n, char s[], int b);

#include <stdio.h>
#include <string.h>

#define MAXLENGTH 30

main()
{
   int n, b;
   b = 16;
   n = -(3*b*b + 2*b + 10);
   n = 0x80000000;
   char s[MAXLENGTH];

   itob(n, s, b);
   printf("n = %d, %s\n", n, s);
   return 0;
}

/* reverse:  reverse string s in place */
void reverse(char s[])
{
   int c, i, j;
   
   for (i = 0, j = strlen(s)-1; i < j; i++, j--)
      c = s[i], s[i] = s[j], s[j] = c;
}

void itob(int n, char s[], int b)
{
   int sign, exception;
   int i = 0;

   if ((sign = n) < 0)
      n = -n;
   exception = n == -n ? 1 : 0;
/*
   int remainder;
   do {
      remainder = n % b;
      remainder = exception ? -remainder : remainder;
      s[i++] = remainder >= 10 ? (remainder-10+'A') : (remainder + '0');
   } while ((n/=b) != 0);
*/
   int tmp;    // the same as remainder
   do
      s[i++] = (tmp=n%b, (tmp=(exception?(-tmp):tmp))) >= 10 ? (tmp-10+'A') : (tmp + '0');
   while ((n /= b) != 0);
   if (sign < 0)
      s[i++] = '-';
   s[i] = '\0';
   reverse(s);
}
