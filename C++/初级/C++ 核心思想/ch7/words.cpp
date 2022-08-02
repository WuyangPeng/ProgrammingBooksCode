#include <iostream>
#include <string>

using namespace std;

int main()
{  
   int count = 0;
   string word;
   while (cin >> word)
   {  
      count++;
   }

   cout << count << " words.\n";

   return 0;
}
