/*
 * Example code of function cat in Section 7.5
 */

#include <stdio.h>
#include <time.h>

/* cat:  concatenate files, version 1 */
main(int argc, char *argv[])
{
   FILE *fp;
   void filecopy(FILE *, FILE *);
   
   long start, end;
   start = clock();
   if (argc == 1)  /* no args; copy standard input */
      filecopy(stdin, stdout);
   else
      while (--argc > 0)
         if ((fp = fopen(*++argv, "r")) == NULL) {
            printf("cat: can't open %s\n", *argv);
            return 1;
         } else {
            filecopy(fp, stdout);
            fclose(fp);
         }
   end = clock();
   printf("time: %f\n", (double)(end - start) / (CLOCKS_PER_SEC));
   return 0;
}

/* filecopy:  copy file ifp to file ofp */
void filecopy(FILE *ifp, FILE *ofp)
{
   int c;
   
   while ((c = getc(ifp)) != EOF)
      putc(c, ofp);
}
