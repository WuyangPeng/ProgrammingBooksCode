// Ex9_04.cpp
// Using the protected access specifier
#include <iostream>                    // For stream I/O
#include "CandyBox.h"                  // For CBox and CCandyBox

int main()
{
  CCandyBox myCandyBox;
  CCandyBox myToffeeBox{ 2, 3, 4, "Stickjaw Toffee" };
  std::cout << "myCandyBox volume is " << myCandyBox.volume() << std::endl
            << "myToffeeBox volume is " << myToffeeBox.volume() << std::endl;

  // std::cout << myToffeeBox.m_Length;  // Uncomment this for an error

  return 0;
}
