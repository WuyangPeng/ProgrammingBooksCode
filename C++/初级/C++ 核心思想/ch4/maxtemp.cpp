#include <iostream>

using namespace std;

int main()
{  
   double next;
   double highest;

   cout << "Please enter the temperature values:\n";
   if (cin >> next)
      highest = next;
   else
   {  
      cout << "No data!\n";
      return 1;
   }

   while (cin >> next)
   {  
      if (next > highest)
         highest = next;
   }

   cout << "The highest temperature is " << highest << "\n";

   return 0;
}
