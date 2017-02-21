/*
 * example of quicksort in text
 */

#include <stdio.h>

void qsort(int v[], int left, int right)
{
   int i, last;
   void swap(int v[], int i, int j);
   
   if (left >= right)
      return;
   swap(v, left, (left + right)/2);
   last = left;
   for (i = left+1; i <= right; i++)
      if (v[i] < v[left])
         swap(v, ++last, i);
   swap(v, left, last);
   qsort(v, left, last-1);
   qsort(v, last+1, right);
}

void swap(int v[], int i, int j)
{
   int temp;
   
   temp = v[i];
   v[i] = v[j];
   v[j] = temp;
}

main()
{
   int v[] = {5, 4, 1, 3, 2};
   int left = 0;
   int right = 4;
   qsort(v, left, right);
   int i;
   for (i=0; i<=right; ++i)
      printf("%d ", v[i]);
   printf("\n");
   return 0;
}
