// Soln8_02.cpp

#include <iostream>                   // For stream input/output
#include <cstring>

using std::cout;
using std::endl;

class CSimpleString
{
private:
   size_t len;
   char* buff;
public:
   CSimpleString(const char* p = nullptr);
   CSimpleString(const CSimpleString& s);
   ~CSimpleString();

   CSimpleString& operator=(const CSimpleString& rhs);
   void print();
};

// Constructor
CSimpleString::CSimpleString(const char* p) : len(0), buff(nullptr)
{
   if (p != nullptr)
   {
      len = strlen(p);
      if (len > 0)
      {
         buff = new char[len+1];
         strcpy_s(buff, len+1, p);
      }
   }
}

// Copy constructor
CSimpleString::CSimpleString(const CSimpleString& s)
{
   len = s.len;
   buff = new char[len+1];
   strcpy_s(buff, len+1, s.buff);
}

// Destructor
CSimpleString::~CSimpleString()
{
   delete[] buff;
}

// Assignment operator - does not deal with str = str
CSimpleString& CSimpleString::operator=(const CSimpleString& rhs)
{
   len = rhs.len;
   delete[] buff;
   buff = new char[len+1];
   strcpy_s(buff, len+1, rhs.buff);

   return *this;
}

void CSimpleString::print()
{
   cout << buff;
}

int main()
{
   CSimpleString s1 = "hello";
   CSimpleString s2 = "goodbye";
   cout << "s1: \"";
   s1.print();
   cout << "\"" << endl;

   cout << "s2: \"";
   s2.print();
   cout << "\"" << endl;

   cout << " After executing s2 = s1:" << endl;
   s2 = s1;

   cout << "s1 = \"";
   s1.print();
   cout << "\"" << endl;

   cout << "s2 = \"";
   s2.print();
   cout << "\"" << endl;

   return 0;
}
