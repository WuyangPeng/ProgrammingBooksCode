#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{  
   int i;
   for (i = 1; i <= 10; i++)
   {  
      int r = rand();
      cout << r << "\n";
   }
   return 0;
}
