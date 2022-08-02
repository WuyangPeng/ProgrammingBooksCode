#include <iostream>
#include <string>

using namespace std;

int main()
{  
   string last;
   string word;
   while (cin >> word)
   {  
      if (word != last)
         cout << word << "\n";
      last = word;
   }
   return 0;
}
