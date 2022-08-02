#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main()
{  
   double area;
   cout << "Please enter the area of a square: ";
   cin >> area;

   if (area >= 0)
      cout << "The side length is " << sqrt(area) << "\n";
   else
      cout << "Error: Negative area.\n";

   return 0;
}
