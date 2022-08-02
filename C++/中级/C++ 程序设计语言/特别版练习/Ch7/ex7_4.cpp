/* Code for exercise 7.4.
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

#include <fstream>
#include <iostream>

void cat_stream(istream &input) {
   char ch;
   while (input.get(ch))
      cout.put(ch);
}

int main(int argc, char *argv[]) {
   if (argc<2) {
      cat_stream(cin);
   } else {
      for (int k = 1; k!=argc; ++k) {
         ifstream infile(argv[k]);
         cat_stream(infile);
      }
   }
   return 0;
}

