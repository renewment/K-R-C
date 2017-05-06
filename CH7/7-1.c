/*
 * Exercise 7-1: Write a program that converts upper case to lower or lower case
 * to upper, depending on the name it is invoked with, as found in argv[0].
 */

#include <stdio.h>
#include <ctype.h>

main(int argc, char *argv[])
{
   int c;
   int (*fp)(int);
   
   if (*(argv[0]+2) == 'u')   // execute program as ./name,
      fp = toupper;           // so check if the third character is 'u'
   else
      fp = tolower;
   while ((c=getchar()) != EOF)
      putchar((*fp)(c));
   
   return 0;
}
