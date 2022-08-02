/* Code for exercise 4.4.
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

// Note: Some compilers do not like the repeated "for (int k ..."
// statement. A common trick to work around that anachronism, is to
// define the following macro:
// #define for if (0) ; else for

#include <iostream>

char const char_table[] =
   "abcdefghijklmnopqrstuvwxyz0123456789-*&@. \\~";

int main() {
   // Do not include the terminating null of chartable!
   // Decimal first:
   for (int k = 0; k<sizeof(char_table)-1; ++k)
      std::cout << char_table[k] << '\t'
                << dec << int(char_table[k]) << std::endl;
    // Or, since dec is the default:
    for (int k = 0; k<sizeof(char_table)-1; ++k)
       std::cout << char_table[k] << '\t'
                 << int(char_table[k]) << std::endl;
   // Hexadecimal:
   for (int k = 0; k<sizeof(char_table); ++k)
      std::cout << char_table[k] << '\t'
                << hex << int(char_table[k]) << std::endl;
   return 0;
}

