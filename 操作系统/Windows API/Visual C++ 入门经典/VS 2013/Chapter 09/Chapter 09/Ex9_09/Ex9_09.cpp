// Ex9_09.cpp
// Using a reference to call a virtual function
#include <iostream>
#include "GlassBox.h"                   // For CBox and CGlassBox

void output(const CBox& aBox);          // Function prototype

int main()
{
  CBox myBox{ 2.0, 3.0, 4.0 };           // Define a base box
  CGlassBox myGlassBox{ 2.0, 3.0, 4.0 }; // Define derived box of same size
  output(myBox);                         // Output volume of base class object
  output(myGlassBox);                    // Output volume of derived class object

  return 0;
}

void output(const CBox& aBox)
{
  aBox.showVolume();
}
