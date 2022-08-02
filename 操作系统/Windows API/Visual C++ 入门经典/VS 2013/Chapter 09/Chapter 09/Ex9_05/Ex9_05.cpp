// Ex9_05.cpp
// Using the copy constrcutor in a derived class
#include <iostream>                                // For stream I/O
#include "CandyBox.h"                              // For CBox and CCandyBox

int main()
{
  CCandyBox chocBox{ 2.0, 3.0, 4.0, "Chockies" };  // Declare and initialize
  CCandyBox chocolateBox{ chocBox };               // Use copy constructor

  std::cout << "Volume of chocBox is " << chocBox.volume() << std::endl
            << "Volume of chocolateBox is " << chocolateBox.volume() << std::endl;

  return 0;
}
