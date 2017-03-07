/*
 * Exercise 5-9: Rewrite the routines  day_of_year  and  month_day with pointers
 * instead of indexing.
 */
#include <stdio.h>

static char daytab[2][13] = {
   {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
   {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};
int day_of_year(int, int, int);
int month_day(int, int, int *, int *);

main()
{
   int m, d, yd;
   if (!month_day(1988, 367, &m, &d))
      printf("the 60th day of 1988 year is %d/%d\n", m, d);
   m = 12, d = 31;
   if ((yd = day_of_year(1988, m, d)) != -1)
      printf("%d/%d is %dth day of 1988 year\n", m, d, yd);
   return 0;
}

/* day_of_year:  set day of year from month & day */
int day_of_year(int year, int month, int day)
{
   int i, leap;
   char *p;
   if (year < 0) {
      printf("error, wrong year\n");
      return -1;
   }
   leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;
   if (month > 12 || month < 1 || day > daytab[leap][month]) {
      printf("error, wrong month and/or day\n");
      return -1;
   }
   for (p = *(daytab+leap); month > 0; p++, month--)
      day += (int)(*p);
   return day;
}

int month_day(int year, int yearday, int *pmonth, int *pday)
{
   int i, leap;
   char *p;
   if (year < 0) {
      printf("error, wrong year\n");
      return -1;
   }
   leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;
   
   for (p = *(daytab+leap), i = 0; i < 12 && yearday - *p > 0; ++i, ++p)
      yearday -= (int)*p;
   if (yearday > 31) {
      printf("error, wrong day of year\n");
      return -1;
   }
   *pmonth = i;
   *pday = yearday;
   return 0;
}
