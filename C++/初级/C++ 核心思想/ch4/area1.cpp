#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main()
{  
   double area;
   cout << "Please enter the area of a square: ";
   cin >> area;
   if (area < 0)
   {  
      cout << "Error: Negative area.\n";
      return 1;
   }

   /* now we know that area is >= 0  */

   double length = sqrt(area);
   cout << "The side length of the square is " 
      << length << "\n";

   return 0;
}
