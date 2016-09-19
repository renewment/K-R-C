/*
 * Write a function reverse(s) that reverse the character string s.
 * Use it to write a program that reverse its input a line at a time.
 */

#include <stdio.h>
#define MAXLENGTH 100

int getString(char s[], int lim);
void reverse(char s[], int length);

main()
{
   int length;
   char s[MAXLENGTH];
   
   while ((length = getString(s , MAXLENGTH)) > 0 ) {
      reverse(s, length);
      printf("%s\n" , s);
   }
   return 0;
}

int getString(char s[], int lim)
{
   int i;
   char c;
   
   for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
      s[i] = c;
      
   s[i] = '\0';
   
   return i;
}

void reverse(char s[], int length)
{
   int i;
   char c;
   
   for (i = 0; i < length/2; ++i) {
      c = s[i];
      s[i] = s[length-i-1];
      s[length-i-1] = c;
   }
}
