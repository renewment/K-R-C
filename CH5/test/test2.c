/*
 * Example code of function day_of_year and month_day
 */
#include <stdio.h>

static int daytab[2][5] = {
   { 0, -1, -2, -3, -4},
   {-5, -6, -7, -8, -9},
};
static int year[5] = {1, 2, 3, 4, 5};
int *p1;
int **p2;
/*
 * type of  daytab : int (*)[5]
 *          *daytab: int *
 */
int day_of_year(int, int, int);
void month_day(int, int, int *, int *);

int   main()
{
   printf("(int)    daytab    = %d\n", (int) daytab);
   // type of daytab is int (*)[13]
   printf("(int)    daytab+1  = %d\n", (int) daytab+1);
   // equivelant to ((int)daytab) + 1,
   // which point to the second byte of first int
   
   printf("(int)    (daytab+1)= %d\n", (int) (daytab+1));
   // (daytab+1) would point to the start of second row
   
   printf("(int)   *daytab    = %d\n", (int) *daytab);
   // type of *daytab is int *
   
   printf("(int)   *daytab+1  = %d\n", (int) *daytab+1);
   // equivalent to ((int)*daytab) + 1
   
   printf("(int)  *(daytab+1) = %d\n", (int) *(daytab+1));
   // the result would be (int)daytab + sizeof(int) * 5
   // type of *(daytab+1) is int *
   
   printf("(int)  **daytab    = %d\n", (int) **daytab);
   // type of **daytab is int;
   // point to the first element of daytab
   
   printf("(int) **daytab + 1 = %d\n", (int) **daytab+1);
   // equivalent to ((int) **daytab) + 1
   
   printf("(int) *(*daytab+1) = %d\n", (int) *(*daytab+1));
   // equivalent to daytab[0][1]
   printf("(int) *(*daytab+1) = %d\n", (int) *(*daytab+1));
   
   //p1 = *daytab;
   p2 = &(*daytab);
   return 0;
}
