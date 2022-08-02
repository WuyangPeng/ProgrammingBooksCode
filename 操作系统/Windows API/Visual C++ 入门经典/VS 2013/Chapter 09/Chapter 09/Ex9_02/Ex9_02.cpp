// Ex9_02.cpp
// Using a function inherited from a base class
#include <iostream>                                          // For stream I/O
#include "CandyBox.h"                                        // For CBox and CCandyBox

int main()
{
  CBox myBox{ 4.0, 3.0, 2.0 };                               // Create CBox object
  CCandyBox myCandyBox;
  CCandyBox myMintBox{ "Wafer Thin Mints" };                 // Create CCandyBox object

  std::cout << "myBox occupies " << sizeof  myBox            // Show how much memory
            << " bytes" << std::endl                         // the objects require
            << "myCandyBox occupies " << sizeof myCandyBox
            << " bytes" << std::endl
            << "myMintBox occupies " << sizeof myMintBox
            << " bytes" << std::endl;
  std::cout << "myMintBox volume is " << myMintBox.volume()  // Get volume of a 
            << std::endl;                                    // CCandyBox object  
  return 0;
}
