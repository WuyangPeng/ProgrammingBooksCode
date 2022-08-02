/* Code for exercise 21.13.
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
#include <stdlib.h>


struct MappedFile {
   struct CharProxy {
      CharProxy(std::fstream &file, std::fstream::off_type pos)
         : file_(file), pos_(pos) {}
      CharProxy& operator=(char c) {
         file_.seekp(pos_);
         file_.put(c);
         return *this;
      }
      operator char() {
         file_.seekg(pos_);
         return char(file_.get());
      }
   private:
      std::fstream &file_;
      std::fstream::off_type pos_;
   };

   MappedFile(std::fstream &file): file_(file) {}
   char operator[](std::fstream::off_type i) const {
      file_.seekg(i);
      return char(file_.peek());
   }
   CharProxy operator[](std::fstream::off_type i) {
      return CharProxy(file_, i);
   }
private:
   std::fstream &file_;
};


void error(char const *prog, char const *entity, char const *msg) {
   std::cerr << prog << ": " << entity << msg << '\n';
   exit(1);
}


int main(int argc, char *argv[]) {
   if (argc!=2)
      error(argv[0], "", ": unexpected number of arguments.");
   std::fstream pass0(argv[1]);
   if (!pass0)
      error(argv[0], argv[1], ": cannot open file for reading.");
   std::fstream::off_type n = 0;
   int chksum0 = 0;
   while (pass0) {
      chksum0 += char(pass0.get());
      ++n;
   }
   std::cerr << "Reading " << n << " characters.\n";
   std::cerr << chksum0 << '\n';
   int chksum1 = 0;
   std::fstream pass1(argv[1]);
   if (!pass1)
      error(argv[0], argv[1], ": cannot open file for reading.");
   MappedFile accessor(pass1);
   std::cerr << "Odd-even exchange...\n";
   for (size_t k = 1; k<n; k += 2) {
      char tmp = accessor[k-1];
      accessor[k-1] = char(accessor[k]);
      accessor[k] = tmp;
   }
   pass1.clear(); // Because the previous pass may have caused the EOF
                  // bit to be set.
   for (size_t k = 0; k!=n; ++k) {
      chksum1 += accessor[k];
   }
   std::cerr << chksum1 << '\n';
   return 0;
}

