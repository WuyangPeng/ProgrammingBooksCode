 /* '05 Main.cpp' */

 /* Input output stream header*/
#include <iostream>

void AddPrintEnergy (short EnergyToAdd);

main ()
{
 AddPrintEnergy (10);
 AddPrintEnergy (10);
 AddPrintEnergy (10);
 AddPrintEnergy (10);

 return 0;
}

void AddPrintEnergy (short EnergyToAdd)
{
 static short Energy = 0;

 Energy += EnergyToAdd;

 std::cout << Energy << std::endl;
}
