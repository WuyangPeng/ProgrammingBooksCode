// Ex9_10.cpp
// Using an abstract class
#include "Box.h"                       // For CBox and CContainer
#include "Can.h"                       // For CCan (and CContainer)
#include <iostream>                    // For stream I/O

int main()
{
  // Pointer to abstract base class
  // initialized with address of CBox object
  CContainer* pC1{ new CBox{ 2.0, 3.0, 4.0 } };

  // Pointer to abstract base class
  // initialized with address of CCan object
  CContainer* pC2{ new CCan{ 6.5, 3.0 } };

  pC1->showVolume();                   // Output the volumes of the two
  pC2->showVolume();                   // objects pointed to

  delete pC1;                          // Now clean up ... 
  delete pC2;                          // ... the free store

  return 0;
}
