// Soln8_03.cpp
// Move semantics requires a move copy constructor and a move assignment operator to be implemented.
// To trace constructor and operator function calls, uncommenting the next line
//#define TRACE

#include <iostream>                                        // For stream input/output
#include <cstring>

using std::cout;
using std::endl;

class CSimpleString
{
private:
  size_t len{};
  char* buff{};
public:
  CSimpleString(const char* p = nullptr);
  CSimpleString(const CSimpleString& s);
  CSimpleString(CSimpleString&& s);                        // Move copy constructor

  CSimpleString(char c, int count = 1);
  CSimpleString(int i);

  ~CSimpleString();

  CSimpleString& operator=(const CSimpleString& rhs);     // Assignment operator
  CSimpleString& operator=(CSimpleString&& rhs);          // Move assignment operator
  void print();
};

// Contructor - repeated given character
CSimpleString::CSimpleString(char c, int count)
{
#ifdef TRACE
  cout << "Construction from repeated character\n";
#endif
  len = count;
  if (len)
  {
    buff = new char[len + 1];
    memset(buff, c, len);
    buff[len] = '\0';
  }
}

// Constructor - from an integer
CSimpleString::CSimpleString(int i)
{
#ifdef TRACE
  cout << "Contruction from an integer.\n";
#endif
  char sTmp[20];
  _itoa_s(i, sTmp, _countof(sTmp), 10);

  len = strlen(sTmp);
  if (len)
  {
    buff = new char[len + 1];
    strcpy_s(buff, len + 1, sTmp);
  }
}

// Constructor
CSimpleString::CSimpleString(const char* p)
{
#ifdef TRACE
  cout << "Contruction from a string.\n";
#endif
  if (p)
  {
    len = strlen(p);
    if (len)
    {
      buff = new char[len + 1];
      strcpy_s(buff, len + 1, p);
    }
  }
}

// Copy constructor
CSimpleString::CSimpleString(const CSimpleString& s)
{
#ifdef TRACE
  cout << "Copy constructor.\n";
#endif
  len = s.len;
  buff = new char[len + 1];
  strcpy_s(buff, len + 1, s.buff);
}

// Move copy constructor
CSimpleString::CSimpleString(CSimpleString&& s)
{
#ifdef TRACE
  cout << "Move copy constructor.\n";
#endif
  len = s.len;
  buff = s.buff;
  s.buff = nullptr;                                        // Prevent the string from being deleted
}

// Destructor
CSimpleString::~CSimpleString()
{
#ifdef TRACE
  cout << "Destructor.\n";
#endif
  delete[] buff;
}

// Assignment operator - does not deal with str = str
CSimpleString& CSimpleString::operator=(const CSimpleString& rhs)
{
#ifdef TRACE
  cout << "Assignment operator.\n";
#endif
  len = rhs.len;
  delete buff;
  buff = new char[len + 1];
  strcpy_s(buff, len + 1, rhs.buff);

  return *this;
}

// Move assignment operator
CSimpleString& CSimpleString::operator=(CSimpleString&& rhs)
{
#ifdef TRACE
  cout << "Move assignment operator.\n";
#endif
  len = rhs.len;
  buff = rhs.buff;
  rhs.buff = nullptr;
  return *this;
}

void CSimpleString::print()
{
  cout << buff;
}

int main()
{
  CSimpleString marker{ '*', 30 };
  CSimpleString s1{ "hello" };
  CSimpleString s2;

  // Test assignment
  marker.print();
  cout << endl;
  cout << "s1 is \"";
  s1.print();
  cout << "\" and s2 is empty.\n";

  s2 = s1;

  cout << " After s2 = s1, s2 is \"";
  s2.print();
  cout << endl;
  marker.print();
  cout << endl;

  // Test construction from an integer
  int n = 7890;

  CSimpleString nStr{ n };

  cout << n << " as a string is \"";
  nStr.print();
  cout << "\"" << endl;
  marker.print();
  cout << endl;

  // Test move constructor
  cout << "Move construction:\n";
  CSimpleString s3{ CSimpleString{ "goodbye" } };
  s3.print();
  cout << endl;
  marker.print();
  cout << endl;

  // Test move assignment
  cout << "Move assignment:\n";
  s3 = CSimpleString{ "toodlepip" };
  s3.print();
  cout << endl;
  marker.print();
  cout << endl;
}
