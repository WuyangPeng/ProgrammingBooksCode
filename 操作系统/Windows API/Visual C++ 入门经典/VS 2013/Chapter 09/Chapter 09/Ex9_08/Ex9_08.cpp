// Ex9_08.cpp
// Using a base class pointer to call a virtual function
#include <iostream>
#include "GlassBox.h"                     // For CBox and CGlassBox

int main()
{
  CBox myBox{ 2.0, 3.0, 4.0 };            // Define a base box
  CGlassBox myGlassBox{ 2.0, 3.0, 4.0 };  // Define derived box of same size
  CBox* pBox{};                           // A pointer to base class objects
  pBox = &myBox;                          // Set pointer to address of base object
  pBox->showVolume();                     // Display volume of base box
  pBox = &myGlassBox;                     // Set pointer to derived class object
  pBox->showVolume();                     // Display volume of derived box

  return 0;
}
