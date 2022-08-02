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

#include <iostream>
#include <typeinfo>

template<typename T>
struct Type {
   static void print() { 
      std::cout << "sizeof(" << typeid(T).name() << ") = "
                << sizeof(T) << std::endl;
   }
};

struct Polymorph {
   virtual ~Polymorph() {}
};

enum Bit { zero, one };
enum Intensity { black = 0, brightest = 1000 };

int main() {
   // Fundamental integral types:
   Type<bool>::print(); // May not be one (but can be).
   Type<char>::print(); // This must be one!
   Type<signed char>::print();
   Type<unsigned char>::print();
   Type<wchar_t>::print(); // No signed/unsigned variants.
   Type<signed short>::print();
   Type<unsigned short>::print();
   Type<signed int>::print();
   Type<unsigned int>::print();
   Type<signed long>::print();
   Type<unsigned long>::print();
#ifdef LONGLONG_EXT
   Type<signed long long>::print();
   Type<unsigned long long>::print();
#endif

   // Fundamental floating-point types:
   Type<float>::print();
   Type<double>::print();
   Type<long double>::print();

   // Pointer types:
   Type<int*>::print();
   Type<int (*)()>::print(); // Pointer to function
      // Pointer to member function:
   Type<void (Polymorph::*)()>::print(); 
   Type<void*>::print(); // May be larger than int* (rare)

   // Enumeration types:
   Type<Bit>::print();
   Type<Intensity>::print();
   return 0;
}

