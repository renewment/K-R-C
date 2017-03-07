/*
 * Page 102-103
 * Test the scenario that if there are two buffer, I want to allocate space from
 * the buffer which has more space. To check which buffer has more space, can I
 * use pointer comparison?
 */

#include <stdio.h>
#define MAXLENGTH 10000
char buf1[MAXLENGTH];
char buf2[MAXLENGTH];
char *bp1 = buf1;
char *bp2 = buf2;

int main()
{
   char *p1 = bp1;
   bp1 += 1000;

   char buf3[MAXLENGTH];
   char *bp3 = buf3;
   
   char *p3 = bp3;
   bp3 += 2000;
   
   // test which buffer has more space
   if ((buf1 + MAXLENGTH - bp1) > (buf3 + MAXLENGTH - bp3))
      printf("space in buffer1 is more than that in buffer3's\n");
   else
      printf("space in buffer3 is more than that in buffer1's\n");
   
   // verify what will happen if I compare bp1 to bp2
   if (bp1 > bp3)
      printf("bp1 > bp3\n");
   else if (bp1 == bp3)
      printf("bp1 == bp3\n");
   else
      printf("bp1 < bp3\n");
   
   // print out the value of buf1 and buf2
   printf("buf1: %d\nbuf3: %d\n" , (int)buf1, (int)buf3);
   return 0;
}
