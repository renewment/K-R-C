/*
 * Exercise 5-5: Write versions of the library functions strncpy, strncat, and
 * strncmp, which operate on at most the  first n characters of their argument
 * strings. For example, strncpy(s,t,n) copies at most n characters of t to s.
 * Full descriptions are in Appendix B.
 */

#include <stdio.h>
#include <string.h>

#define SIZE 100
void sstrncpy(char *s, char *t, int);
void sstrncat(char *s, char *t, int);
int sstrncmp(char *s, char *t, int);

main()
{
   char s[SIZE] = "abcdefgh";
   char t[] = "12345";
   sstrncpy(s, t, 4);       // s should be "1234"
   printf("%s\n", s);
   sstrncat(s, "4321", 3);  // s should be "1234432"
   printf("%s\n", s);
   printf("%d\n", sstrncmp(s, "222222", 3));
   return 0;
}

void sstrncpy(char *s, char *t, int n)
{
   for (; n > 0; --n)
      *s++ = *t ? *t++ : *t;
   *s = '\0';
}

void sstrncat(char *s, char *t, int n)
{
   while (*s)
      ++s;
   for (; n > 0 && *t; --n)
      *s++ = *t++;
   *s = '\0';
}

int sstrncmp(char *s, char *t, int n)
{
   for (; n > 0 && *s == *t; --n, ++s, ++t)
      ;
   if (n)
      return *s - *t;
   else
      return 0;
}
