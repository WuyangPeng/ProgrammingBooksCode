/* Code for exercise 21.1.
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

#include <complex>
#include <fstream>
#include <iostream>
#include <stdlib.h>

void error(char const *prog, char const *entity,
           char const *msg) {
   std::cerr << prog << ": " << entity << msg << '\n';
   exit(1);
}

int main(int argc, char *argv[]) {
   if (argc!=2)
      error(argv[0], "", ": unexpected number of arguments.");
   std::ifstream numbers(argv[1]);
   if (!numbers)
      error(argv[0], argv[1], ": cannot open file for reading.");
   double re, im;
   while (numbers >> re) {
      if (numbers >> im)
         std::cout << std::complex<double>(re, im) << '\n';
      else
         std::cout << std::complex<double>(re, 0.0)
                   << "\nWarning: odd number of values.\n";
   }
   return 0;
}

