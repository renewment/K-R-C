/*
 * Exercise 7-3: Revise minprintf to handle more of the other facilities of
 * printf.
 *
 * when \t or \x00 or other escape sequences appear in the format string,
 * compiler (or other machanism) will convert them into another symbol.
 * so if you want to use minprintf to print \x00 and you write as
 *
 *    minprintf("\x30")
 *
 * , it is equivalent to that you write 
 * 
 *    minprintf("0")
 *
 * the actually read symbol is "0" rather than "\\x30"
 */

#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

/* minprintf:  minimal printf with variable argument list */
void minprintf(char *fmt, ...)
{
   va_list ap;   /* points to each unnamed arg in turn */
   char *p, *sval;
   int ival;
   unsigned int uval;
   double dval;
   void *pval;
   
   va_start(ap, fmt); /* make ap point to 1st unnamed arg */
   for (p = fmt; *p; p++) {
      if (*p != '%' && *p != '\\') {
         putchar(*p);
         continue;
      }
      if (*p == '%')
         switch (*++p) {
         case 'd': case 'i':
            ival = va_arg(ap, int);
            printf("%d", ival);
            break;
         case 'o':
            ival = va_arg(ap, int);
            printf("%o", ival);
            break;
         case 'x': case 'X':
            ival = va_arg(ap, int);
            printf((*p == 'x')? "%x" : "%X", ival);
            break;
         case 'u':
            uval = va_arg(ap, unsigned int);
            printf("%u", uval);
            break;
         case 'c':
            ival = va_arg(ap, int);
            printf("%c", ival);
            break;
         case 's':
            for (sval = va_arg(ap, char *); *sval; sval++)
               putchar(*sval);
            break;
         case 'f':
            dval = va_arg(ap, double);
            printf("%f", dval);
            break;
         case 'e':
            dval = va_arg(ap, double);
            printf("%e", dval);
            break;
         case 'E':
            dval = va_arg(ap, double);
            printf("%E", dval);
            break;
         case 'g':
            dval = va_arg(ap, double);
            printf("%g", dval);
            break;
         case 'G':
            dval = va_arg(ap, double);
            printf("%G", dval);
            break;
         case 'p':
            pval = va_arg(ap, void *);
            printf("%p", pval);
            break;
         case '%':
            printf("%%");
            break;
         default:
            putchar(*p);
            break;
         }
      else if (*p == '\n')
         putchar('\n');
      else if (*p == '\t')
         putchar('\t');
      else if (*p == '\v')
         putchar('\v');
      else if (*p == '\b')
         putchar('\b');
      else if (*p == '\r')
         putchar('\r');
      else if (*p == '\f')
         putchar('\f');
      else if (*p == '\a')
         putchar('\a');
      else if (*p == '\\')
         putchar('\\');
      else if (*p == '\?')
         putchar('\?');
      else if (*p == '\'')
         putchar('\'');
      else if (*p == '\"')
         putchar('\"');
      else
         putchar(*p);
   }
   va_end(ap);
}

main()
{
   int n = 50;
   unsigned int u = 0xffffffff;
   char str[] = "fuu";
   double d = 0.031415;
   int *p = &n;
   
   // conversion sppecifications
   minprintf("%%d: %d\n", n);
   minprintf("%%i: %i\n", n);
   minprintf("%%o: %o\n", n);
   minprintf("%%x: %x\n", n);
   minprintf("%%X: %X\n", n);
   minprintf("%%u: %u\n", u);
   minprintf("%%c: %c\n", n);
   minprintf("%%s: %s\n", str);
   minprintf("%%f: %f\n", d);
   minprintf("%%e: %e\n", d);
   minprintf("%%E: %E\n", d);
   minprintf("%%g: %g\n", d);
   minprintf("%%G: %G\n", d);
   minprintf("%%p: %p\n", p);
   minprintf("%%%%: %%\n");
   
   // escape sequences
   minprintf("\\n: n\nn\n");
   minprintf("\\t: t\tt\n");
   minprintf("\\v: v\vv\n");
   minprintf("\\b: b\bb\n");
   minprintf("\\r: r\rr\n");
   minprintf("\\f: f\ff\n");
   minprintf("\\a: a\aa\n");
   minprintf("\\\\: back slash\\\n");
   minprintf("\\\?: question mark\?\n");
   minprintf("\\\': single quote\'\n");
   minprintf("\\\": double quote\"\n");
   minprintf("\\60: char \60\n");
   minprintf("\\x30: char \x30\n");
   return 0;
}
