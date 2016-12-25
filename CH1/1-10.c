/*
 * Exercise 1-10. Write a program to copy its input to its output, replacing
 * each tab by \t, each backspace by \b, and each backslash by \\. This makes
 * tabs and backspaces visible in an unambiguous way.
 */

/*
 * to enter backspace:
 * http://stackoverflow.com/questions/20142215/not-being-able-to-get-backspace-character-b-in-the-output-on-ubuntu-kr-exam
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
