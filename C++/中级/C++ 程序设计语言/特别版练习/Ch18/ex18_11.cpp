/* Code for exercise 18.11.
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
#include <fstream>
#include <iostream>
#include <string>

void error(char const *name, char const *msg) {
   std::cerr << name << msg << '\n';
   std::exit(1);
}

int main(int argc, char *argv[]) {
   using std::string;
   if (argc!=3)
      error(argv[0], ": Unexpected number of arguments.\n");
   std::ifstream instream(argv[1]);
   std::ofstream outstream(argv[2]);
   if (not instream or not outstream)
      error(instream? argv[2]: argv[1],
            ": cannot open file.\n");
   std::istream_iterator<string, char> in(instream), in_end;
   std::ostream_iterator<string, char> out(outstream, " ");
   std::unique_copy(in, in_end, out);
   return 0;
}

