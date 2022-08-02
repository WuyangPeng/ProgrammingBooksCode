// Soln5_2.cpp
#include <iostream>
using std::cout;
using std::endl;

// Swap two integers
void swap(int* pa, int* pb)
{
   int temp = *pa;
   *pa = *pb;
   *pb = temp;
}

int main()
{
   int a=6, b=4;
   cout << "Before swap:" << endl;
   cout << "a = " << a << ", b = " << b << endl;

   swap(&a, &b);
   cout << "After swap:" << endl;
   cout << "a = " << a << ", b = " << b << endl;
   return 0;
}
