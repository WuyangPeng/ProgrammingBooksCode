#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main()
{  
   double area;
   cout << "Please enter the area of a square: ";
   cin >> area;

   if (cin.fail())
   {
      cout << "Error: Bad input\n";
      return 1;
   }

   if (area < 0)
   {
      cout << "Error: Negative area.\n";
      return 1;
   }

   cout << "The side length is " << sqrt(area) << "\n";

   return 0;
}
