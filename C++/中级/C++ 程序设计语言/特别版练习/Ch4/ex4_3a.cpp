/* Code for exercise 4.3.
 | 
 | "C++ Solutions--Companion to The C++ Programming Language, Third Edition"
 | by David Vandevoorde; Addison-Wesley 1998; ISBN 0-201-30965-3.
 |
 | Permission to use, copy, modify, distribute and sell this software
 | and its documentation for any purpose is hereby granted without fee.
 | The author makes no representations about the suitability of this
 | software for any purpose.  It is provided "as is" without express or
 | implied warranty.
 `----------------------------------------------------------------------*/

// Some compilers still have <iostream.h> instead of <iostream>
#include <iostream>

// Omit the following using-declaration if your compiler
// doesn't place cout in namespace std:
using std::cout;

struct Polymorph {
   virtual ~Polymorph() {}
};

enum Bit { zero, one };
enum Intensity { black = 0, brightest = 1000 };

int main() {
   // Fundamental integral types:
   cout << "sizeof(bool)==" << sizeof(bool) << '\n';
      // sizeof(bool) may not be one (but it can be).
   cout << "sizeof(char)==" << sizeof(char) << '\n';
   cout << "sizeof(signed char)=="
        << sizeof(signed char) << '\n';
   cout << "sizeof(unsigned char)=="
        << sizeof(unsigned char) << '\n';
   cout << "sizeof(wchar_t)==" << sizeof(wchar_t) << '\n';
      // There are no signed/unsigned variants of wchar_t.
   cout << "sizeof(signed short)=="
        << sizeof(signed short) << '\n';
   cout << "sizeof(unsigned short)=="
        << sizeof(unsigned short) << '\n';
   cout << "sizeof(signed int)=="
        << sizeof(signed int) << '\n';
   cout << "sizeof(unsigned int)=="
        << sizeof(unsigned int) << '\n';
   cout << "sizeof(signed long)=="
        << sizeof(signed long) << '\n';
   cout << "sizeof(unsigned long)=="
        << sizeof(unsigned long) << '\n';
#ifdef LONGLONG_EXT
   cout << "sizeof(signed long long)=="
        << sizeof(signed long long) << '\n';
   cout << "sizeof(unsigned long long)=="
        << sizeof(unsigned long long) << '\n';
#endif

   // Fundamental floating-point types:
   cout << "sizeof(float)==" << sizeof(float) << '\n';
   cout << "sizeof(double)==" << sizeof(double) << '\n';
   cout << "sizeof(long double)=="
        << sizeof(long double) << '\n';

   // Pointer types:
   cout << "sizeof(int*)==" << sizeof(int*) << '\n';
   cout << "sizeof(int (*)())=="
        << sizeof(int (*)()) << '\n';
      // The above corresponds to a pointer to a function.
      // Next is a pointer to a member function:
   cout << "sizeof(void (Polymorph::*)())==" 
        << sizeof(void (Polymorph::*)()) << '\n';
   cout << "sizeof(void*)==" << sizeof(void*) << '\n';

   // Enumeration types:
   cout << "sizeof(Bit)==" << sizeof(Bit) << '\n';
   cout << "sizeof(Intensity)=="
        << sizeof(Intensity) << '\n';
   return 0;
}

