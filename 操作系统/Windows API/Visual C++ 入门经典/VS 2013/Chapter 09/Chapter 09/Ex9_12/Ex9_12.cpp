// Ex9_12.cpp
// Destructor calls with derived classes using objects via a base class pointer
#include "Box.h"                           // For CBox and CContainer
#include "Can.h"                           // For CCan (and CContainer)
#include "GlassBox.h"                      // For CGlassBox (and CBox and CContainer)
#include <iostream>                        // For stream I/O

int main()
{
  // Pointer to abstract base class initialized with CBox object address
  CContainer* pC1{ new CBox{ 2.0, 3.0, 4.0 } };
  CCan myCan{ 6.5, 3.0 };
  CGlassBox myGlassBox{ 2.0, 3.0, 4.0 };
  pC1->showVolume();                       // Output the volume of CBox
  std::cout << "Delete CBox" << std::endl;
  delete pC1;                              // Now clean up the free store
  pC1 = new CGlassBox{ 4.0, 5.0, 6.0 };     // Create CGlassBox dynamically
  pC1->showVolume();                       // ...output its volume...
  std::cout << "Delete CGlassBox" << std::endl;
  delete pC1;                              // ...and delete it
  pC1 = &myCan;                            // Get myCan address in pointer
  pC1->showVolume();                       // Output the volume of CCan
  pC1 = &myGlassBox;                       // Get myGlassBox address in pointer
  pC1->showVolume();                       // Output the volume of CGlassBox

  return 0;
}
