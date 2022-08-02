 /* '03 Main.cpp' */

 /* Input output stream header*/
#include <iostream>

 /* Use default parameter for IVA - 17% */
void CalculateIVA (long Money, double IVA = 0.17);

main ()
{
 std::cout << "Specifying the IVA value : 1000" << std::endl;
 CalculateIVA (1000, 0.12);

 std::cout << "Using the default IVA value : 1000" << std::endl;
 CalculateIVA (1000);

 return 0;
}

void CalculateIVA (long Money, double IVA)
{
 double MoneyWithIVA;
  
  /* Calculate IVA */
 MoneyWithIVA = Money * IVA;

 std::cout << "Money after IVA at " << IVA << " is " << MoneyWithIVA;
 std::cout << std::endl;
}
