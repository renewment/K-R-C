/*
 * Page 104
 * test what will happen if I try to modify a string constant by a char pointer
 * point to that string
 */

#include <stdio.h>

int main()
{
   char *ptr = "abcde";                   // ptr is a pointer points to string
                                          // constant "abcde\0"
   printf("original string: %s\n", ptr);
   *ptr = 'f';                            // trying to modify string constant
                                          // will make bus error occur
   printf("modified string: %s\n", ptr);
   return 0;
}
