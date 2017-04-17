#include <stdio.h>

enum e {A = 1, B} fuu;
enum {C = 3, D} fuu2;
enum {E = 5, F};
enum e2;
struct {
   int x;
   int y;
};
struct pos{
   int x;
   int y;
};
int main()
{
   enum e qq;
   fuu = A;
   qq = B;
   fuu2 = C;
   printf("fuu = %d, qq = %d\n\n", fuu, qq);
   printf("fuu2 = %d\n", fuu2);
   qq = E;
   printf("qq = %d\n", qq);
   return 0;
}
