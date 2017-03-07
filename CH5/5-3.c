/*
 * Exercise 5-3: Write a pointer version of the function strcat that we showed
 * in Chapter 2: strcat(s,t) copies the string t to the end fo s.
 */

#include <stdio.h>

#define SIZE 100
void strcatt(char *s, char *t);

main()
{
   char s[SIZE] = "abcde";
   char t[] = "fghijk";
   strcatt(s, t);
   printf("%s\n", s);
   return 0;
}

void strcatt(char *s, char *t)
{
   while (*s)
      ++s;
   while ((*s++ = *t++))
      ;
}
