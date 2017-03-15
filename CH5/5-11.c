/*
 * Exercise 5-11: Modify the program entab and detab (written as exercises in
 * Chapter 1) to acceept a list of tab stops as arguments. Use the default tab
 * settings if there are no arguments.
 */

#include <stdio.h>
#include <stdlib.h>   /* for atof() */

#define N 8

void entab(int);
void detab(int);

main(int argc, char *argv[])
{
   int flagDetab = 0, flagEntab = 0, stops = N;
   char c;
   while (--argc && (*++argv)[0] == '-')
      switch (c = *(++*argv)) {
      case 'e':
         flagEntab = 1;
         break;
      case 'd':
         flagDetab = 1;
         break;
      case 's':
         --argc;
         stops = atoi(*++argv);
         break;
      default :
         printf("illegal option %c\n", c);
         printf("Usage: ./a.out [-e|-d] [-s NUM]\n");
         break;
      }
   if (argc) {
      printf("error, illegal option %c\n", (*argv)[0]);
      return -1;
   }
   if (flagEntab & flagDetab) {
      printf("option can be either -e or -d\n");
      return -1;
   } else if (flagEntab)
      entab(stops);
   else if (flagDetab)
      detab(stops);
   return 0;
}

#define MAXLENGTH 1000

void entab(int stops)
{
   int counter = 0, position = 0, index = 0;
   char c, str[MAXLENGTH];
   while ( (c=getchar()) != EOF) {
      switch (c) {
      case ' ':
         if (++counter + position == stops) {
            putchar('\t');
            str[index++] = '\\';
            str[index++] = 't';
            counter = position = 0;
         }
         break;
      case '\n':
         while (counter--) {
            putchar(' ');
            str[index++] = '~';
         }
         putchar(c);
         str[index++] = '\\';
         str[index++] = 'n';
         str[index++] = '\0';
         printf("for debug:\n%s\n", str);
         counter = position = index =  0;
         break;
      case '\t':
         putchar(c);
         str[index++] = '\\';
         str[index++] = 't';
         counter = position = 0;
         break;
      default:
         position += counter;
         while (counter--) {
            putchar(' ');
            str[index++] = '~';
         }
         position++;
         putchar(c);
         str[index++] = c;
         counter = 0;
      }
   }
}

void detab(int stops)
{
   int space = stops, index = 0;;
   char c, str[MAXLENGTH];
   while ((c = getchar()) != EOF) {
      switch (c) {
      case '\t':
         while (space--) {
            putchar(' ');
            str[index++] = '~';
         }
         space = stops;
         break;
      case '\n':
         space = stops;
         putchar(c);
         str[index++] = '\\';
         str[index++] = 'n';
         str[index++] = '\0';
         printf("for debug:\n%s\n", str);
         index = 0;
         break;
      case ' ':
         --space;
         putchar(c);
         str[index++] = '~';
         break;
      default:
         --space;
         putchar(c);
         str[index++] = c;
         break;
      }
   }
}
