// Soln5_5.cpp
#include <iostream>
#include <cstring>
using std::cin;
using std::cout;
using std::endl;
 
char* parse(const char* str)
{
   static char* pStr(nullptr);
   static size_t len(0);
   static size_t start(0);
   size_t pos(0);
   char* pReturn(nullptr);

   // First time through, save the string
   if (str)
   {
      delete[] pStr;   // in case it was allocated
      len = strlen(str);
      pStr = new char[len+1];
      strcpy_s(pStr, len+1, str);
   }

   if (start >= len)
      return nullptr;

   // Walk the string from 'start' till we find a blank or the end
   for (pos = start; pStr[pos] != ' ' && pStr[pos] != '\0'; pos++);

   // Copy the string if we've a word to return, otherwise return nullptr
   if (pos != start)
   {
      pReturn = new char[pos - start + 2];
      size_t i(0);
      for (size_t j=start; j<pos; i++,j++)
         pReturn[i] = pStr[j];
      pReturn[i] = '\0';
      start = pos+1;
      return pReturn;
   }
   else
   {
	  delete[] pStr;             // We are done with the string
	  pStr = nullptr;
      return nullptr;
   }
}

int main()
{
   char s1[] = "seventy-one fruit balls, please Doris";
   cout << "string is '" << s1 << "'\n\nParsing...\n";
   char* p = parse(s1);

   while (p)
   {
      cout << p << endl;
	  delete[] p;                // Delete the string that was returned
      p = parse(nullptr);
   }

   return 0;
}
