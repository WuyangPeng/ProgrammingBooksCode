/* Code for exercise 16.1.
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

#include <algorithm>
#include <vector>
#include <iostream>
#include <iterator>

/* This program presents problems for compilers whose standard library
   only takes a single template argument for ostream_iterator. In that
   case the second argument can be left off. */

char const L[] = "abcdefghijklmnopqrstuvwxyz";

int main() {
   using std::copy;
   std::vector<char> alphabet(&L[0], &L[0]+sizeof(L));
   copy(alphabet.begin(), alphabet.end(),
        std::ostream_iterator<char, char>(std::cout, " "));
   std::cout << '\n';
   copy(alphabet.rbegin(), alphabet.rend(),
        std::ostream_iterator<char, char>(std::cout, " "));
   std::cout << '\n';
   return 0;
}

