/*
 * Write a program to remove trailing blanks and tabs from
 * each line of input, and to delete entirely blank line.
 */

#include <stdio.h>
#define MAXLINE 100
#define TRUE    1
#define FALSE   0

int readline(char line[], int lim);

main()
{
   int len;
   char line[MAXLINE];
   
   while((len = readline(line, MAXLINE)) != 0)
      if (len != -1)
         printf("%s\n", line);
   
   return 0;
}

int readline(char line[], int lim)
{
   int i, blankCounter, tabCounter, noCharacter;
   char c;
   
   blankCounter = tabCounter = 0;
   noCharacter = TRUE;
   
   for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i) {
      if (c == ' ') {
         if (blankCounter == 0)
            line[i] = c;
         else
            --i;
         ++blankCounter;
      }
      else if (c == '\t') {
         if (tabCounter == 0)
            line[i] = c;
         else
            --i;
         ++tabCounter;
      } else {
         noCharacter = FALSE;
         line[i] = c;
         blankCounter = tabCounter = 0;
      }
   }
   
   if (c == EOF)
      return 0;
   if (noCharacter) {
      line[0] = '\0';
      return -1;
   } else
      line[i] = '\0';
   return i;
}
