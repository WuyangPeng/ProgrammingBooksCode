// Soln5_5.cpp
#include <iostream>
#include <cstring>
 
char* parse(const char* str)
{
  static char* pStr{};
  static size_t len{};
  static size_t start{};
  size_t pos{};
  char* pReturn{};

  // First time through, save the string
  if (str)
  {
     delete pStr;                              // in case it was allocated
     len = strlen(str);
     pStr = new char[len+1];
     strcpy_s(pStr, len+1, str);
  }

  if (start >= len)
     return nullptr;

  // Walk the string from 'start' till we find a blank or the end
  for (pos = start; pStr[pos] != ' ' && pStr[pos] != '\0'; ++pos);

  // Copy the string if we've a word to return, otherwise return NULL
  if (pos != start)
  {
    pReturn = new char[pos - start + 2];
    size_t i{};
    for (size_t j{ start }; j < pos; ++i, ++j)
      pReturn[i] = pStr[j];
      pReturn[i] = '\0';
      start = pos + 1;
      return pReturn;
   }
   else
     return nullptr;
}

int main()
{
  char s1[] {"seventy-one fruit balls, please Doris"};
  std::cout << "string is '" << s1 << "'\n\nParsing...\n";
  char* p{ parse(s1) };

   while (p)
   {
     std::cout << p << std::endl;
      delete[] p;
      p = parse(nullptr);
   }
}
