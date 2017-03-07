#include <stdio.h>

/*
 1.
 explicitly declared that daytab is a 2-d array with the size of it
 void foo(char daytab[2][13])
 
 2.
 explicitly declared daytab as a 2-d array, but only specify the # of column,
 compiler can use this information to infer in which row any element is
 void foo(char daytab[][13])
 
 3.
 in function parameter declaration, *daytab is equivilent to daytab[], which 
 means that daytab is a pointer. however, since brackets [] have higher 
 precedence than *, parentheses are needed to insure the order of parsing.
 void foo(char (*daytab)[13])
 
 4.
 daytab is declared as a array, each of whose elements is a pointer.
 So in this declaration, daytab actully is a ** pointer.
 void foo(char *daytab[13])
 */
main()
{
   int a[10] = {0};
   int *p = a;
   int b = 1;
/*
   printf("p = %d\n", (int)p);
   printf("??? = %d\n", (int)*((int*)1534749488)); // no error when compilation,
   *(int*)1534749488 = 1;                          // but segmentation fault
                                                   // when run-time
 */
/*
   *p++ = 1;   // equivalent to *(p++) = 1;
   *(p++) = 1; // *p = 1, p = p + 1;
   (*p)++ = 1; // error, (*p) is not an lvalue, since the result of (*p) is a
               // tempary value in register, and can't be addressed by &(*p)
   *++p = 1;   // p = p + 1; *p = 1;
   *(++p) = 1; // equivalent to *++p = 1;
   ++*p = 1;   // error, ++*p is not an lvalue
               // (*p = *p + 1) = 1;
   ++(*p) = 1; // error, equivalent to ++*p = 1;
 */
   
   char daytab[2][13] = {
      {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
      {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
   };       // a 2-d array is actually a 1-d array,
            // so in some occasion daytab can be seemed as a char * type pointer
   return 0;
}

