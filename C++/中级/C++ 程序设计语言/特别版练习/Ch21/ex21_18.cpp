/* Code for exercise 21.18.
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

#include <assert.h>
#include <iostream>
#include <stdexcept>
#include <string>

namespace { // unnamed namespace
   char ext_digits[] =
      "0123456789abcdefghijklmnopqrstuvwxyz";
} // end unnamed namespace

struct based {
   based(int b, int v): base_(b), value_(v) {
      if (b<2 or b>sizeof(ext_digits))
         throw std::invalid_argument(std::string("based"));
   }
   int base() const { return base_; }
   int value() const { return value_; }
private:
   int base_, value_;
};


std::ostream& operator<<(std::ostream &output, based v) {
   int const bufsize = 130; // Enough for 128 base-2 digits
   char buffer[bufsize];
   int value = v.value(), base = v.base();
   bool negative = value<0;
   if (negative)
      value = -value;
   int endpos = bufsize;
   buffer[--endpos] = '\0'; // C-string termination
   do {
      buffer[--endpos] = ext_digits[value%base];
      assert(endpos>0);
   } while (value /= base);
   if (negative)
      buffer[--endpos] = '-';
   return output << &buffer[endpos];
}


int main() {
   std::cout << "31 in base 16 is " << based(16, 31) << '\n';
   return 0;
}

