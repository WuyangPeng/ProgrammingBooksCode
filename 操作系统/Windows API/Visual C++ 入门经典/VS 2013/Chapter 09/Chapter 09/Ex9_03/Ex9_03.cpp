// Ex9_03.cpp
// Calling a base constructor from a derived class constructor
#include <iostream>                    // For stream I/O
#include "CandyBox.h"                  // For CBox and CCandyBox

int main()
{
  CBox myBox{ 4.0, 3.0, 2.0 };
  CCandyBox myCandyBox;
  CCandyBox myMintBox{ 1.0, 2.0, 3.0, "Wafer Thin Mints" };
  std::cout << "myBox occupies " << sizeof  myBox     // Show how much memory
    << " bytes" << std::endl                  // the objects require
    << "myCandyBox occupies " << sizeof myCandyBox
    << " bytes" << std::endl
    << "myMintBox occupies " << sizeof myMintBox
    << " bytes" << std::endl;

  std::cout << "myMintBox volume is "                 // Get volume of a
    << myMintBox.volume() << std::endl;       // CCandyBox object

  return 0;
}
