// Ex9_06.cpp
// Behavior of inherited functions in a derived class
#include <iostream>
#include "GlassBox.h"                   // For CBox and CGlassBox

int main()
{
  CBox myBox{ 2.0, 3.0, 4.0 };           // Define a base box
  CGlassBox myGlassBox{ 2.0, 3.0, 4.0 }; // Define derived box - same size

  myBox.showVolume();                   // Display volume of base box
  myGlassBox.showVolume();              // Display volume of derived box
  return 0;
}
