// Soln2_2.cpp
#include <iostream>

/*
 Shifting number right 3 positions with the expression (number >> 3) divides the value by 8 and discards the remainder.
 Shifting the result of the previous operation left by 3 positions with the expression ((number >> 3) << 3) multiplies
 it by 8 so you get the value of number less the remainder R after dividing by 8 i.e. (number - R)
 Subtracting (number - R) from number gives just R, which is what you are looking for.
*/

int main()
{
  int number {};

   std::cout << "Enter a number: ";
   std::cin >> number;

   atd::cout << "Thank you. The remainder after dividing your number by 8 is " 
             << number - ((number >> 3) << 3)
             << endl;

   return 0;
}
