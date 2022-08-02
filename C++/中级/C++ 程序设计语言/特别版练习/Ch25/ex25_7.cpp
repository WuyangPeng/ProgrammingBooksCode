/* Code for exercise 25.7.
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

template<typename T, T low, T high>
struct Range {
   struct Error {};
   Range(T value): value_(value) {
      if (value>=high || value<low)
         throw Error();
   }
   Range& operator=(Range &r) { this->value_ = r.value_; }
   Range& operator=(T value) { return *this = Range(value); }
   operator T() { return value_; }
private:
   T value_;
};


extern double const low = -1.0, high = 1.0;
Range<double const&, low, high> val(0.0);

int main() {
   try {
      val = 2.0;
   } catch (...) {
      std::cout << "Whoops! Caught something.\n";
   }
   return 0;
}

