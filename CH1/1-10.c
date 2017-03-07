/*
 * Exercise 1-10. Write a program to copy its input to its output, replacing
 * each tab by \t, each backspace by \b, and each backslash by \\. This makes
 * tabs and backspaces visible in an unambiguous way.
 *
 * to enter backspace:
 * https://goo.gl/JWdsof
 */

#include <stdio.h>

main()
{
   char c;
   while ((c = getchar()) != EOF) {
      if (c != '\t')
         if (c != '\b')
            if (c != '\\')
               putchar(c);

      if (c == '\t')
         printf("\\t");
      if (c == '\b')
         printf("\\b");
      if (c == '\\')
          printf("\\\\");
   }
}
