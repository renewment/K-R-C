/*
 * Example code of function find
 */

#include <stdio.h>
#include <string.h>
#define MAXLINE 10000

int getLine(char *line, int max);

/* find:  print lines that match pattern from 1st arg */
main(int argc, char *argv[])
{
   char line[MAXLINE];
   long lineno = 0;
   int c, except = 0, number = 0, found = 0;
   
   printf("at very first,\nargv: %d\t*argv: %d\n", (int) argv, (int) *argv);
   while (--argc > 0 && (*++argv)[0] == '-') {
      printf("\targv: %d\t*argv: %d\n", (int) argv, (int) *argv);
      while (c = *++argv[0]) {
         printf("\t\targv: %d\t*argv: %d\n", (int) argv, (int) *argv);
         switch (c) {
         case 'x':
            except = 1;
            break;
         case 'n':
            number = 1;
            break;
         default:
            printf("find: illegal option %c\n", c);
            argc = 0;
            found = -1;
            break;
         }
      }
   }
   if (argc != 1)
      printf("Usage: find -x -n pattern\n");
   else
      while (getLine(line, MAXLINE) > 0) {
         lineno++;
         if ((strstr(line, *argv) != NULL) != except) {
            if (number)
               printf("%ld:", lineno);
             printf("%s", line);
             found++;
         }
      }
   return found;
}

int getLine(char s[], int lim)
{
   int c, i;
   
   for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
      s[i] = c;
   if (c == '\n') {
      s[i] = c;
      ++i;
   }
   s[i] = '\0';
   return i;
}
