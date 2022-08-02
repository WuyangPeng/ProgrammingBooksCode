/* Code for exercise 4.5.
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
#include <limits>
#include <typeinfo>

template<typename T>
struct Type {
   static void print() {
      std::cout << typeid(T).name() << ": range is (" 
                << std::numeric_limits<T>::min() << ", "
                << std::numeric_limits<T>::max() << ")\n";
   }
};

int main() {
   Type<char>::print();
   Type<short>::print();
   Type<int>::print();
   Type<long>::print();
   Type<float>::print();
   Type<double>::print();
   Type<long double>::print(); // Some compilers will not handle this one well
   Type<unsigned>::print();
   return 0;
}

