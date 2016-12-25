/*
 * Exercise 1-15. Rewrite the temperature conversion program of Section 1.2 to
 * use a function for conversion
 */

#include <stdio.h>

float convert(float);

main()
{
   float fahr, celsius;
   int lower, upper, step;
   
   lower = 0;
   upper = 300;
   step = 20;
   
   fahr = lower;
   while (fahr <= upper) {
      celsius = convert(fahr);
      printf("%3.0f %6.1f\n", fahr, celsius);
      fahr = fahr + step;
   }
   return 0;
}

float convert(float fahr)
{
   float celsius;
   
   celsius = (5.0/9.0) * (fahr-32.0);
   return celsius;
}
