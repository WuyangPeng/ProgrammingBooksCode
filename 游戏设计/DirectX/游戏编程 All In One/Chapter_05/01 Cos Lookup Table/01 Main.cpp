 /* '01 Main.cpp' */

 /* Input output stream header file */
#include <iostream>
 /* C++ math header file */
#include <math.h>

 /* Start */
main (void)
{
  /* Declare look up table */
 double COSTable [360]; /* 360 elements for all angles between 0 and 359 */
 int Number;

  /* Calculate look up table */
 std::cout << "Calculating Cosine look up table..." << std::endl;

 for (Number = 0; Number < 360; Number++)
 {
  COSTable [Number] = cos (Number * 3.14159 / 180);
 }

  /* Calculate Cosine of 50000000 values using look up table 
     and then using cos */
 std::cout << "Calculating cosine of 50000000 random values using look";
 std::cout << " up table..." << std::endl;
  /* Look up table */
 for (Number = 0; Number < 50000000; Number++)
 {
  COSTable [rand () % 360];
 }

 std::cout << "Calculating cosine of 50000000 random values using cos";
 std::cout << " function..." << std::endl;
  /* cos function */
 for (Number = 0; Number < 50000000; Number++)
 {
  cos (rand () % 360);
 }


 return 0;
}