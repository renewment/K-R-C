/*
 * Exercise 7-9: Functions like isupper can be implemented to save space or to
 * save time. Explore both possibilities.
 */

int isupper(int c)
{
   return (c >= 'A' && c <= 'Z') ? 1 : 0;
}

#define isupper(x) ((x) >= 'A' && (x) <= 'Z') ? 1 : 0
