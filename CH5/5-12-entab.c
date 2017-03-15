/*
 * Exercise 5-12: Extend entab and detab to accept the shsorthand
 *        entab -m +n
 * to mean tab stops every n columns, starting at column m. Choose convenient (
 * for the user) default behavior.
 */

#include <stdio.h>
#include <stdlib.h>   /* for atof() */

#define N 8
#define MAXLENGTH 1000

int entab(int, int, char *);

main(int argc, char *argv[])
{
   int m = 0, n = N;
   char c, str[MAXLENGTH];
   while (--argc)
      switch (c = **++argv) {
      case '-':
            m = atoi(++*argv);
            break;
      case '+':
            n = atoi(++*argv);
            break;
      default:
            printf("Illegal option\n");
            printf("Usage ./a.out -m -n, where m and n are column indexes starting from 1\n");
            break;
      }
   while ( entab(m, n, str) > 0)
      printf("for debg,\n%s\n", str);
   return 0;
}

int entab(int m, int n, char *str)
{
   int length = 0, counter = 0, position = 0;
   char c = '\0';
   while ((c=getchar()) != EOF && c != '\n') {
      if (m > 0) {
         if (c == '\t' && m - n >= 0) {
            putchar(c);
            *str++ = '\\';
            *str++ = 't';
            m -= n;
         } else if (c == '\t')
            while (m--) {
               putchar(' ');
               *str++ = '~';
            }
         else {
            putchar(c);
            *str++ = c;
            --m;
         }
      } else {
         switch (c) {
         case ' ':
            if (++counter + position == n) {
               putchar('\t');
               *str++ = '\\';
               *str++ = 't';
               ++length;
               counter = position = 0;
            }
            break;
         case '\t':
            putchar(c);
            *str++ = '\\';
            *str++ = 't';
            ++length;
            counter = position = 0;
            break;
         default:
            length += counter;
            while (counter--) {
               putchar(' ');
               *str++ = '~';
               ++position;
            }
            counter = 0;
            ++position;
            putchar(c);
            *str++ = c;
            break;
         }
      }
   }
   if (c == '\n') {
      putchar(c);
      *str++ = '\\';
      *str++ = 'n';
      ++length;
   }
   *str = '\0';
   return length;
}
