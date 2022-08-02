// Soln2_4.cpp
#include <iostream>
using std::cout;
using std::endl;

/* As specified the program calculates the aspect ration by dividing one integer value by another.
   The result of this is always an integer  so it is a very poor measure of the aspect ratio
   in general.
   A much better way is to carry out the calculation using floating-point arithmetic. To do this
   you just need to cast either of the operands for the division to a floating-point type, as shown below.
   The compiler will arrange for the other operand to be converted to the same type.
*/

int main()
{
   int width = 1280;
   int height = 1024;
//   double aspect = width / height;
   double aspect = static_cast<double>(width) / height;

   cout << "The aspect ratio is " 
        << aspect;
   cout << endl;

   return 0;
}
