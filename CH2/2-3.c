/*
 * Exercise 2-3. Write the function htoi(s), which converts a string of hexa-
 * decimal digits (including an optional 0x or 0X) into its equivalent integer
 * value. The allowable digits are 0 through 9, a through f, and A through F.
 */

#include <stdio.h>
#define base 16
#define length 11

main()
{
   char c;
   char hex[length];
   long value = 0;
   int counter = 0;
   
   if ( (c=getchar()) == '0' )
   {
      hex[counter] = c;
      ++counter;
      c = getchar();
      if ( c == 'x' || c == 'X' )
         ;
      else if (c >= '0' && c <= '9')
         value = value * base + (c - '0');
      else if (c >= 'a' && c <= 'f')
         value = value * base + (c - 'a' + 10);
      else if (c >= 'A' && c <= 'F')
         value = value * base + (c - 'A' + 10);
      else {
         printf("char %c is not allowed in hexa-decimal\n" , c);
         return -1;
      }
   }
   else if (c > '0' && c <= '9')
      value = value * base + (c - '0');
   else if (c >= 'a' && c <= 'f')
      value = value * base + (c - 'a' + 10);
   else if (c >= 'A' && c <= 'F')
      value = value * base + (c - 'A' + 10);
   else {
      printf("char %c is not allowed in hexa-decimal\n" , c);
      return -1;
   }
   hex[counter] = c;
   ++counter;
   while((c = getchar()) != '\n' && counter < length-1) {
      if (c >= '0' && c <= '9')
         value = value * base + (c - '0');
      else if (c >= 'a' && c <= 'f')
         value = value * base + (c - 'a' + 10);
      else if (c >= 'A' && c <= 'F')
         value = value * base + (c - 'A' + 10);
      else {
         printf("char %c is not allowed in hexa-decimal\n" , c);
         return -1;
      }
      hex[counter] = c;
      ++counter;
   }
   hex[counter] = '\0';
   printf("%s = %ld\n" , hex , value);
   return 0;
}
