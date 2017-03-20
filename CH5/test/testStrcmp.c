/*
 * It's seems that strcmp converts all characters of parameters into unsigned
 * char
 */
#include <stdio.h>
#include <string.h>
int myStrcmp(char*, char*);

int main()
{
   char a[] = {2 , -1  , '\0'},
        b[] = {2 , 1 , '\0'};
   
   printf("strcmp(a, b) = %d\n", strcmp(a, b));
   printf("strcmp(b, a) = %d\n", strcmp(b, a));
   printf("myStrcmp(a, b) = %d\n", myStrcmp(a, b));
   printf("myStrcmp(b, a) = %d\n", myStrcmp(b, a));
   return 0;
}

int myStrcmp(char *s1, char *s2)
{
   for (; *s1 == *s2; ++s1, ++s2)
      if (*s1 == '\0')
         return 0;
   return *s1 - *s2;
}
