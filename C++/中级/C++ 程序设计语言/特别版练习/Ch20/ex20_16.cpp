/* Code for exercise 20.16.
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
#include <string>

std::string itos(int value) {
   // Assume no more than 64 bits (about 20 digits):
   int const bufsize = 20;
   assert(sizeof(int)<=8);
   char buffer[bufsize];
   bool negative = value<0;
   if (negative)
      value = -value;
   int endpos = bufsize;
   do {
      buffer[--endpos] = char('0'+value%10);
   } while (value /= 10);
   if (negative)
      buffer[--endpos] = '-';
   return std::string(&buffer[endpos], bufsize-endpos);
}


int main() {
   std::cout << itos(23*34) << '\n';
   std::cout << itos(-23*34) << '\n';
   return 0;
}

