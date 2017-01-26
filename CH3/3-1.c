/*
 * Exercise 3-1. Our binary search makes two tests inside the loop, when one
 * suffice (at the price of more tests outside). Write a version with only on
 * test inside the loop and measure the difference in run-time.
 */

#include <stdio.h>

int binsearch(int x, int v[], int n);

main()
{
   int x = 8;
   int v[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
   int n = 11;
   
   printf("%d\n" ,  binsearch(x, v, n));
   
   return 0;
}

int binsearch(int x, int v[], int n)
{
   int low, high, mid;
   
   low = 0;
   high = n - 1;
   mid = (low+high) / 2;
   while (x != v[mid] && low <= high) {
      if (x < v[mid])
         high = mid - 1;
      else
         low = mid + 1;
      mid = (low+high) / 2;
   }
   
   return low <= high ? mid : -1;
}
