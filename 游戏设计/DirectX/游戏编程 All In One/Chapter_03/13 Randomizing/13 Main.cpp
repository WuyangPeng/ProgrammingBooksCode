 /* '13 Main.cpp' */

 /* Input output stream header*/
#include <iostream>

main ()
{
 short Value;
 short Dividend = 4; 

  /* Calculate the remainder from 0 to 25 */
 for (Value = 0; Value < 25; Value++)
 {
   /* Show the remainder */
  std::cout << Value << "%" << Dividend << "=" << Value % Dividend;
  std::cout << std::endl;
 }

 return 0;
}
