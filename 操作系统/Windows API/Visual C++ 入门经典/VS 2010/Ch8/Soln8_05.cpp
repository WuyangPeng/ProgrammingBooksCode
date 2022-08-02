// Soln8_05.cpp

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
   CSimpleString(char c, int count=1);
   CSimpleString(int i);
   ~CSimpleString();

   CSimpleString& operator=(const CSimpleString& rhs);
   CSimpleString& operator+=(const CSimpleString& rhs);
   CSimpleString operator+(const CSimpleString& s);
   CSimpleString operator+(const char* s);
   void print();
};

CSimpleString::CSimpleString(char c, int count) : len(0), buff(nullptr)
{
   len = count;
   if (len > 0)
   {
      buff = new char[len+1];
      memset(buff, c, len);
      buff[len] = '\0';
   }
}

CSimpleString::CSimpleString(int i) : len(0), buff(nullptr)
{
   char sTmp[20];
   _itoa_s(i, sTmp, 20, 10);

   len = strlen(sTmp);
   if (len > 0)
   {
      buff = new char[len+1];
      strcpy_s(buff, len+1, sTmp);
   }
}

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

CSimpleString::CSimpleString(const CSimpleString& s)
{
   len = s.len;
   buff = new char[len+1];
   strcpy_s(buff, len+1, s.buff);
}

CSimpleString::~CSimpleString()
{
   delete[] buff;
}

// Assignment operator - does deal with str = str
CSimpleString& CSimpleString::operator=(const CSimpleString& rhs)
{
   if (&rhs != this)
   {
     len = rhs.len;
     delete[] buff;
     buff = new char[len+1];
     strcpy_s(buff, len+1, rhs.buff);
   }

   return *this;
}

// Addition operator: add two CSimpleString objects
CSimpleString CSimpleString::operator+(const CSimpleString& s)
{
  size_t length = len + s.len + 1;
   char* tmp = new char[length];
   strcpy_s(tmp, length, buff);
   strcat_s(tmp, length, s.buff);

   return CSimpleString(tmp);
}

// Addition operator: CSimpleString object + string constant
CSimpleString CSimpleString::operator+(const char* s)
{
  return *this + CSimpleString(s);
}

// += operator
CSimpleString& CSimpleString::operator+=(const CSimpleString& rhs)
{
   *this = *this + rhs;
   return *this;
}

void CSimpleString::print()
{
   cout << buff;
}

int main()
{
   CSimpleString s1 = "hello";
   CSimpleString s2;

   s2 = s1;
   CSimpleString marker = CSimpleString('*', 30);
   marker.print();
   cout << endl;

   cout << "s1 = \"";
   s1.print();

   cout << "\"" << endl;

   cout << "s2 = \"";
   s2.print();
   cout << "\"" << endl;

   int n = 7890;

   CSimpleString nStr = CSimpleString(n);

   cout << n << " as a string is \"";
   nStr.print();
   cout << "\"" << endl;

   CSimpleString* pStr = &s2;

   s2 = *pStr;      // s2 = s2
   cout << "s2 = \"";
   s2.print();
   cout << "\"" << endl;

   s1 += " world!";

   cout << "s1 = \"";
   s1.print();

   cout << "\"" << endl;

   marker.print();
   cout << endl;
   return 0;
}
