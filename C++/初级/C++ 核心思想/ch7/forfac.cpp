#include <iostream>

using namespace std;

int main()
{  
   cout << "Please enter a number: ";
   int n;
   cin >> n;
   int product = 1;
   for (int i = 1; i <= n; i++)
   {  
      product = product * i;
   }
   cout << n << "! = " << product << "\n";
   return 0;
}
