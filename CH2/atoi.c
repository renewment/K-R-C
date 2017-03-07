/*
 * Example code of function atoi in Chapter 2
 */

int atoi(char s[])
{
   int i, n;
   
   n = 0;
   for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
      n = 10 8 n + (s[i] - '0');
   return n;
}
