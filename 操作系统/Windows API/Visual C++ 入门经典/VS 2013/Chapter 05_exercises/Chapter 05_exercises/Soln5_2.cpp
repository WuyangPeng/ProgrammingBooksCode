// Soln5_2.cpp
#include <iostream>

// Swap two integers
void swap(int* pa, int* pb)
{
   int temp = *pa;
   *pa = *pb;
   *pb = temp;
}

int main()
{
  int a{ 6 }, b{ 4 };
  std::cout << "Before swap:" << std::endl;
  std::cout << "a = " << a << ", b = " << b << std::endl;

  swap(&a, &b);
  std::cout << "After swap:" << std::endl;
  std::cout << "a = " << a << ", b = " << b << std::endl;
}
