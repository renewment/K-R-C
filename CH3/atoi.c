/*
 * Example code of function atoi in Chapter 3
 */

int atoi(char s[])
{
   int i, n, sign;
   
   for (i = 0; isspace(s[i]); i++)  /* skip white space */
      ;
   sign = (s[i] == '-') ? -1 : 1;
   if (s[i] == '+' || s[i] == '-')  /* skip sign */
      i++;
   for (n = 0; isdigits(s[i]); i++)
      n = 10 * n + (s[i] - '0');
   return sign * n;
}
