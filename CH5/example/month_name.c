/*
 * Example code of initialization of pointer array
 */

char *month_name(int n)
{
   static char *name[] = {
      "Illegal month",
      "January", "February", "March",
      "April", "May", "June",
      "July", "August", "Septtember",
      "October", "November", "December"
   };
   
   return (n < 1 || n > 12) ? name[0] : name[n];
}
