 /* '04 Main.cpp' */

 /* Input Output stream header file */
#include <iostream>

 /* Start */
main (void)
{
 unsigned char ASCIIValue = 0;
 
 while (ASCIIValue < 255)
 {
   /* Output ASCII character */
  std::cout.put (ASCIIValue);
  ASCIIValue ++;
 }

 return 0;
}