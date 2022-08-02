// Soln6_01.cpp
#include <iostream>
#include <cstring>
using std::cin;
using std::cout;
using std::endl;
 
int ascVal(size_t i, const char* p)
{
   // Output the ASCII value of the character
   if (!p || i > strlen(p))
      return -1;
   else
      return p[i];
}

int main()
{
   char* str = "a bunch of bananas";
   int (*fp) (int, const char*);

   fp = ascVal;
   for(size_t n = 0 ; n<strlen(str) ; n++)
   {
     int i = (*fp)(n,str);

     cout << "value of '" << str[n] << "' is " << i << endl;
   }

   return 0;
}
