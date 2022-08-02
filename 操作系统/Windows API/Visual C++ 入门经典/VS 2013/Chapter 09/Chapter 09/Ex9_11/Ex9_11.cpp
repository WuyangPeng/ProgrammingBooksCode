// Ex9_11.cpp
// Using an abstract class with multiple levels of inheritance
#include "Box.h"                        // For CBox and CContainer
#include "Can.h"                        // For CCan (and CContainer)
#include "GlassBox.h"                   // For CGlassBox (and CBox and CContainer)
#include <iostream>                     // For stream I/O

int main()
{
  // Pointer to abstract base class initialized with CBox object address
  CContainer* pC1{ new CBox{ 2.0, 3.0, 4.0 } };
  CCan myCan{ 6.5, 3.0 };                // Define CCan object
  CGlassBox myGlassBox{ 2.0, 3.0, 4.0 }; // Define CGlassBox object
  pC1->showVolume();                     // Output the volume of CBox
  delete pC1;                            // Now clean up the free store

  pC1 = &myCan;                          // Put myCan address in pointer
  pC1->showVolume();                     // Output the volume of CCan
  pC1 = &myGlassBox;                     // Put myGlassBox address in pointer
  pC1->showVolume();                     // Output the volume of CGlassBox

  return 0;
}
