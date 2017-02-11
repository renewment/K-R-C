/*
 * Write a version of itoa that accepts three arguments instead of two. The
 * third argument is a minimum field width; the converted number must be padded
 * with blanks on the left if necessary to make it wide enough.
 */

#include <stdio.h>
#include <string.h>

#define MAXLENGTH 50

void reverse(char s[]);
void itoa(int n, char s[], int length);

main(){
   int n = 0x80000000;
   char s[MAXLENGTH];
   int length = 10;
   
   printf("n = %d\n" , n);
   itoa(n, s, length);
   printf("n in string representatin: %s\n" , s);
   
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

void itoa(int n, char s[], int length)
{
   int i, sign, exception;
   
   if ((sign = n) < 0)
      n = -n;
   exception = n == -n ? 1 : 0;
   i = 0;
   do
      s[i++] = exception ? -(n % 10) + '0' : (n % 10) + '0';
   while ((n /= 10) != 0 || i < length);
   if (sign < 0)
      s[i++] = '-';
   while (i < length)
      s[i++] = ' ';
   s[i] = '\0';
   reverse(s);
}
