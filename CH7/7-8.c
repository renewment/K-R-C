/*
 * Exercise 7-8: Write a program to print a set of files, starting each new one
 * on a new page, with a title and a running page count for each file.
 */

#include <stdio.h>

#define LINEPERPAGE 40
#define MAXLENGTH 100
main(int argc, char *argv[])
{
   FILE *fp;
   int line, page;
   char str[MAXLENGTH];
   
   while (--argc) {
      fp = fopen(*++argv, "r");
      line = -1;
      page = 0;
      printf("file name: %s\n", *argv);
      while (!feof(fp)) {
         if (!(++line % LINEPERPAGE))
            printf("\n----------page %d----------\n", ++page);
         fgets(str, MAXLENGTH, fp);
         printf("%s", str);
      }
      fclose(fp);
      printf("\n\n==========================\n\n");
   }
   return 0;
}
