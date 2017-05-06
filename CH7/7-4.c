/*
 * Exercise 7-4: Write a private version of scanf analogous to minscanf from
 * the previous section.
 */

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

/* minscanf:  minimal scanf with variable argument list */
void minscanf(char *fmt, ...)
{
   va_list ap;   /* points to each unnamed arg in turn */
   char *p, *cptr;
   int *iptr;
   unsigned int *uptr;
   float *fptr;
   long int *lptr;
   double *dptr;
   int exitFlag = 0, numReadV = 0;
   
   va_start(ap, fmt); /* make ap point to 1st unnamed arg */
   for (p = fmt; *p; p++) {
      if (isspace(*p))
         continue;
      if (*p != '%') {
         if (*p == getchar())
            continue;
         else
            break;
      } else {
         switch (*++p) {
         case 'd': case 'i':
            iptr = va_arg(ap, int *);
            numReadV = scanf("%d", iptr);
            break;
         case 'o':
            iptr = va_arg(ap, int *);
            numReadV = scanf("%o", iptr);
            break;
         case 'u':
            uptr = va_arg(ap, unsigned int *);
            numReadV = scanf("%u", uptr);
            break;
         case 'x': case 'X':
            iptr = va_arg(ap, int *);
            numReadV = scanf((*p == 'x')? "%x" : "%X", iptr);
            break;
         case 'c':
            cptr = va_arg(ap, char *);
            numReadV = scanf("%c", cptr);
            break;
         case 's':
            cptr = va_arg(ap, char *);
            numReadV = scanf("%s", cptr);
            break;
         case 'f':
            fptr = va_arg(ap, float *);
            numReadV = scanf("%f", fptr);
            break;
         case 'e':
            fptr = va_arg(ap, float *);
            numReadV = scanf("%e", fptr);
            break;
         case 'g':
            fptr = va_arg(ap, float *);
            numReadV = scanf("%g", fptr);
            break;
         case 'l':
            if (*++p == 'd') {
               lptr = va_arg(ap, long int *);
               numReadV = scanf("%ld", lptr);
            } else {
               dptr = va_arg(ap, double *);
               if (*p == 'f')
                  numReadV = scanf("%lf", dptr);
               else if (*p == 'e')
                  numReadV = scanf("%le", dptr);
               else if (*p == 'g')
                  numReadV = scanf("%lg", dptr);
               else
                  exitFlag = 1;
            }
            break;
         case '%':
            if ('%' != getchar())
               exitFlag = 1;
            break;
         default:
            printf("QQ?!");
            putchar(*p);
            exitFlag = 1;
            break;
         }
         if (!numReadV)
            exitFlag = 1;
      }
      if (exitFlag)
         break;
   }
   va_end(ap);
}

main()
{
   int n;
   unsigned int u;
   char c;
   char str[20] = "";
   double d;
   float f;
   
   printf("n: ");    minscanf("%d", &n);  printf("%d\n", n);
   printf("i: ");    minscanf("%i", &n);  printf("%i\n", n);
   printf("o: ");    minscanf("%o", &n);  printf("%o, %d\n", n, n);
   printf("u: ");    minscanf("%u", &u);  printf("%u\n", u);
   printf("x: ");    minscanf("%x", &n);  printf("%x, %d\n", n, n);
   printf("c: ");    minscanf("%c", &c);  printf("%c\n", c);
   printf("s: ");    minscanf("%s", str); printf("%s\n", str);
   printf("e: ");    minscanf("%e", &f);  printf("%e\n", f);
   printf("f: ");    minscanf("%f", &f);  printf("%f\n", f);
   printf("g: ");    minscanf("%g", &f);  printf("%g\n", f);
   return 0;
}
