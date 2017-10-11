/*
 * Exercise 1-17. Write a program to print all input lines that are longer than
 * 80 characters.
 */

#include <stdio.h>
#define MAXLINE   1000
#define THRESHOLD 80

int copy(char line[], int lim);

main()
{
   int len;
   char line[MAXLINE];
   
   while ((len = copy(line, MAXLINE)) > 0)
      if (len > THRESHOLD)
         printf("length is %d, text is %s\n" , len, line);
      else
         printf("length is %d\n", len);
   
   return 0;
}

int copy(char line[], int lim)
{
   int i;
   char c;
   
   for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n';++i)
      line[i] = c;
   if (c == '\n') {
      line[i] = c;
      ++i;
   }
   line[i] = '\0';
   return i;
}
