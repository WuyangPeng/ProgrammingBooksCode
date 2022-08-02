// Ex2_10.cpp
// Declaring a namespace 
#include <iostream>

namespace myStuff
{
  int value {};
}

int main()
{
  std::cout << "enter an integer: ";
  std::cin  >> myStuff::value;
  std::cout << "\nYou entered " << myStuff::value
            << std:: endl;
  return 0;
}
