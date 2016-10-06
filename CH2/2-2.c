/*
 * for (i=0; i<lim-1 && (c=getchar(()) != '\n' && c != EOF; ++i)
 *     s[i] = c;
 * Write A loop equivalent to the for loop above without using && or ||
 *
 */

#include <stdio.h>

main()
{
   int i = 0, lim = 20;
   int stop = 0;
   char c, s[lim];
   
   while (i < lim-1) {
      c = getchar();
      if (c != '\n') {
         if (c != EOF) {
            s[i] = c;
            ++i;
         }
         else
            stop = 1;
      }
      else
         stop = 1;
      
      if (stop) {
         s[i] = '\0';
         i = lim;
      }
   }
   
   printf("%s\n", s);
   return 0;
}
