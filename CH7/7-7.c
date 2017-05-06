/*
 * Exercise 7-7: Modify the pattern finding program of Chapter 5 to take its
 * input from a set of named files or, if no files are named as arguments, from
 * the standard input. Should the file name be printed when a matching line is
 * found?
 */

#include <stdio.h>
#include <string.h>
#define MAXLINE 10000

int getLine(char *line, int max);

/* find:  print lines that match pattern from 1st arg */
main(int argc, char *argv[])
{
   char line[MAXLINE], pattern[MAXLINE];
   long lineno = 0;
   FILE *fp;
   int c, except = 0, number = 0, found = 0, fileN = 0, i;
   
   while (--argc > 0 && (*++argv)[0] == '-') {
      while (c = *++argv[0]) {
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
   strcpy(pattern, *argv++);
   while (--argc) {
      fp = fopen(*argv, "r");
      printf("in file \"%s\":\n\n", *argv);
      while (fgets(line, MAXLINE, fp)) {
         lineno++;
         if ((strstr(line, pattern) != NULL) != except) {
            if (number)
               printf("%ld:", lineno);
            printf("%s", line);
            found++;
         }
      }
      fclose(fp);
      printf("========================================\n");
      ++argv;
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
