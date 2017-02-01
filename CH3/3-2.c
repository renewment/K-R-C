/*
 * Write a function escape(s,t) that converts characters like neweline and tab
 * into visible escape sequences like \n and \t as it copies the string t to s.
 * Use a switch. Write a function for the other direction as well, converting
 * escape sequences into the real characters.
 */

#include <stdio.h>

void escape(char s[], char t[]);
void unescape(char t[], char s[]);

#define MAXLENGTH 100

main()
{
   char s[MAXLENGTH*2], t[MAXLENGTH];
   char c;
   int count = 0;
   
   while((c = getchar()) != EOF && count < MAXLENGTH - 1)
      t[count++] = c;
   t[count] = '\0';
   
   printf("original string:\n%s\n\n",
          t);
   escape(s, t);
   printf("visibal escape sequence:\n%s\n\n", s);
   t[0] = '\0';
   unescape(t, s);
   printf("invisible escape sequence:\n%s\n", t);
   
   return 0;
}

void escape(char s[], char t[])
{
   int count, i;
   count = 0;
   for (i = 0; t[i] != '\0'; ++i) {
      switch (t[i]) {
      case '\t':
         s[count++] = '\\';
         s[count++] = 't';
         break;
      case '\n':
         s[count++] = '\\';
         s[count++] = 'n';
         break;
      case '\b':
         s[count++] = '\\';
         s[count++] = 'b';
         break;
      default:
         s[count++] = t[i];
         break;
      }
   }
   s[count] = '\0';
}

void unescape(char t[], char s[])
{
   int count, i, isEscape;
   count = i = isEscape = 0;
   while (s[i] != '\0') {
      switch (s[i]) {
      case '\\':
         switch (s[++i]) {
         case 't':
            t[count++] = '\t';
            break;
         case 'n':
            t[count++] = '\n';
            break;
         case 'b':
            t[count++] = '\b';
            break;
         default:
            break;
         }
         ++i;
         break;
      default:
         t[count++] = s[i++];
      }
   }
   t[count] = '\0';
}
