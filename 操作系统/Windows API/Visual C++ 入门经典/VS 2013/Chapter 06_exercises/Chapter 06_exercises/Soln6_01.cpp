// Soln6_01.cpp
#include <iostream>
#include <iomanip>
#include <cstring>
 
int ascVal(size_t i, const char* p)
{
   // Return the ASCII value of the character
   if (!p || i > strlen(p))
      return -1;
   else
      return p[i];
}

int main()
{
  char* str { "a bunch of bananas" };
  int (*fp) (size_t, const char*);

  fp = ascVal;
  for (size_t n{}; n < strlen(str); ++n)
  {
    std::cout << "value of '" << str[n] << "' is "
              << std::setw(3) << std::setiosflags(std::ios_base::right) << fp(n, str)
              << std::endl;
   }
}
