// Ex5_12.cpp
#include <iostream>
using std::cout;
using std::endl;
        
double* treble(double);                     // Function prototype
        
int main()
{
  double num { 5.0 };                       // Test value
  double* ptr {};                           // Pointer to returned value
        
  ptr = treble(num);
        
  cout << endl << "Three times num = " << 3.0*num;
        
  cout << endl << "Result = " << *ptr;      // Display 3*num
        
  cout << endl;
  return 0;
}
        
// Function to treble a value - mark 1
double* treble(double data)
{
  double result {};
  result = 3.0*data;
  return &result;
}
