#include <stdio.h>
#include <unistd.h>
int main()
{
   FILE *fp = fopen("out", "w");
   int i, j;
   for (i = 0; i <= 2; ++i) {
      for (j = 1; j <= 15; ++j) {
         fprintf(fp, "%d", i);
         fprintf(stdout, "%d", i);
         if (j == 5) {
            fprintf(fp, "_____");
            fprintf(stdout, "_____");
            fflush(fp);
            fflush(stdout);
            sleep(1);
         } else if (j == 10) {
            fseek(fp, -8, 1);
            fseek(stdout, -8, 1);
         }
      }
      fprintf(fp, "\n");
      fprintf(stdout, "\n");
   }
   return 0;
}
