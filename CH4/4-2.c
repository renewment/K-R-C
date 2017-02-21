/*
 * Exercise 4-2: Extend atof to handle scientific notatin of the form 123.45e-6
 * where a floating-point number may be followed by e or E and an optionally
 * signed exponent.
 */

#include <stdio.h>
#include <ctype.h>

double atof(char s[]);

main()
{
   char s[] = "123.45e-6";
   double f = atof(s);
   printf("%f\n" , f);
   return 0;
}

double atof(char s[])
{
   double val, power;
   int i, sign;
   int exponent, exponentSign;
   for (i = 0; isspace(s[i]); i++)
      ;
   sign = (s[i] == '-') ? -1 : 1;
   if (s[i] == '+' || s[i] == '-')
      i++;
   for (val = 0.0; isdigit(s[i]); i++)
      val = 10.0 * val + (s[i] - '0');
   if  ( s[i] == '.')
      i++;
   for (power = 1.0; isdigit(s[i]); i++) {
      val = 10.0 * val + (s[i] - '0');
      power *= 10.0;
   }
   val = sign * val / power;
   
   exponentSign = 0;
   if (s[i] == 'e' || s[i] == 'E') {
      if (~isdigit(s[++i]))
         exponentSign = s[i++] == '+' ? 1 : -1;
      for (exponent = 0; isdigit(s[i]); i++)
         exponent = 10.0 * exponent + s[i] - '0';
   }
   if (exponentSign == 1)
      for (; exponent > 0; --exponent)
         val *= 10;
   else if (exponentSign == -1)
      for (; exponent > 0; --exponent)
         val /= 10;
   
   return val;
}
