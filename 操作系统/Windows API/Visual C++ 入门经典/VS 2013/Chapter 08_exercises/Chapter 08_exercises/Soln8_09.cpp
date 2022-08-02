// Soln8_09.cpp
/*
The static indentLevel member of the CTRace class keeps track of the current indent level.
Each time the constructor executes it increments the indent level and each time the destructor
executes it decrements the indent level. Thus the indentLevel value will reflect
the level of nesting of the current block, provided you create a CTrace object at
the start of each block.
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
  char* pstr{};
  static int indentLevel;
};

int CTrace::indentLevel{};      // Indent level

// Constructor
CTrace::CTrace(const char* str)
{
  indentLevel += 2;
  size_t len{ strlen(str) + 1 };
  pstr = new char[len];
  strcpy_s(pstr, len, str);

  for (int i{}; i < indentLevel; i++)
    cout << ' ';

  cout << "Entry: " << pstr << endl;
}

// Destructor
CTrace::~CTrace()
{
  for (int i{}; i < indentLevel; i++)
    cout << ' ';
  cout << "Exit:  " << pstr << endl;
  indentLevel -= 2;
  delete[] pstr;
  pstr = nullptr;
}

void TestIndenting()
{
  CTrace trace{ "Test function" };
}

int main()
{
  CTrace trace{ "Main routine" };

  if (3 > 5)
  {
    CTrace trace1{ "'if' block" };
    TestIndenting();
  }
  else
  {
    CTrace trace2{ "'else' block" };
    TestIndenting();
  }
}
