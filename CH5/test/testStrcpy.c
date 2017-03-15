//

#include <stdio.h>
void strcpyy(char *, char *);

int main()
{
   char s[10] = "";
   char t[10] = "abcde";
   strcpyy(s, t);
   printf("s: %s\nt: %s\n", s, t);
   return 0;
}

void strcpyy(char *s, char *t)
{
   while(( *++s = *(t++)) != '\0')
      ;
   // ++*s -> *s = *s + 1
   // *++s -> s = s + 1, *s
   // *s++ -> *(s++) -> fetch s, operate, then s = s +1
   // *(s++)
   // (*s)++ -> fetch *s, operate, then *s = *s + 1
}
