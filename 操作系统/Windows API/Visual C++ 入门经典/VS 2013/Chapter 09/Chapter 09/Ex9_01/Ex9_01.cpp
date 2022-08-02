// Ex9_01.cpp
// Using a derived class
#include <iostream>                                   // For stream I/O
#include "CandyBox.h"                                 // For CBox and CCandyBox

int main()
{
  CBox myBox{ 4.0, 3.0, 2.0 };                        // Create CBox object
  CCandyBox myCandyBox;
  CCandyBox myMintBox{ "Wafer Thin Mints" };          // Create CCandyBox object

  std::cout << "myBox occupies " << sizeof myBox      // Show how much memory
    << " bytes" << std::endl                  // the objects require
    << "myCandyBox occupies " << sizeof myCandyBox
    << " bytes" << std::endl
    << "myMintBox occupies " << sizeof myMintBox
    << " bytes" << std::endl;

  std::cout << "myBox length is " << myBox.m_Length << std::endl;

  myBox.m_Length = 10.0;

  //   myCandyBox.m_Length = 10.0;       // uncomment this for an error

  return 0;
}
