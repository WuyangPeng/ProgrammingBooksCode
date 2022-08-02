// Soln4_3.cpp
#include <iostream>
#include <string>

int main()
{
  char str[] {"Doctor Livingstone, I presume?"};
  std::cout << str << std::endl;                     // Output the string

  for (size_t i{}; i < strlen(str); i += 2)
   {
      if (str[i] >= 'a' && str[i] <= 'z')            // If it's lowercase letter
         str[i] -= 32;                               // change to uppercase
   }

   std::cout << str << std::endl;                    // Output the modified string
}
