// Soln8_09.cpp
/*
  When you create a CTrace object the constructor outputs a message.
  At the end of the block in which a CTrace object is created on the stack, the object
  will be destroyed automatically and the destructor called.
  The destructor outputs a message to indicate the end of the block.
  Of course a block can be a function or a nested block within a function.
*/

#include <iostream>                   // For stream input/output
#include <cstring>

using std::cout;
using std::endl;

class CTrace
{
public:
   CTrace(const char* str);
   ~CTrace();
private:
   char* pstr;
};

// Constructor
CTrace::CTrace(const char* str)
{
  size_t len = strlen(str)+1;
   pstr = new char[len];
   strcpy_s(pstr, len, str);
   cout << "Entry: " << pstr << endl;
}

// Destructor
CTrace::~CTrace()
{
   cout << "Exit: " << pstr << endl;
   delete[] pstr;
   pstr = nullptr;
}

int main()
{
   CTrace trace("Main routine");

   if (3 > 5)
   {
      CTrace trace1("'if' block");
   }
   else
   {
      CTrace trace2("'else' block");
   }

   return 0;
}
