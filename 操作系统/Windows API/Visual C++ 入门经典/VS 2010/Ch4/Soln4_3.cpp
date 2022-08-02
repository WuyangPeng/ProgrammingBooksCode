// Soln4_3.cpp
#include <iostream>
#include <string>
using std::cout;
using std::endl; 

int main()
{
   char str[] = "Doctor Livingstone, I presume?";
   cout << str << endl;                     // Output the string

   for (unsigned int i = 0; i < strlen(str); i += 2)
   {
      if (str[i] >= 'a' && str[i] <= 'z')   // If it's lowercase letter
         str[i] -= 32;                      // change to uppercase
   }

   cout << str << endl;                     // Output the modified string
   return 0;
}
