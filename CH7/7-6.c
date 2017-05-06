/*
 * Exercise 7-6: Write a program to compare two files, printing the first line
 * where they differ.
 */

#include <stdio.h>
#include <string.h>
#define MAXLENGTH 100

main(int argc, char *argv[])
{
   FILE *f1 = fopen(argv[1], "r");
   FILE *f2 = fopen(argv[2], "r");
   char str1[MAXLENGTH], str2[MAXLENGTH];
   while (!feof(f1)) {
      fgets(str1, MAXLENGTH-1, f1);
      fgets(str2, MAXLENGTH-1, f2);
      if (strcmp(str1, str2))
         break;
   }
   if (!feof(f1)) {
      printf("in %s, %s\n", argv[1], str1);
      printf("in %s, %s\n", argv[2], str2);
   } else
      printf("%s and %s have the same contents\n", argv[1], argv[2]);
   return 0;
}
