/* Code for exercise 12.9.
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

#include <iostream.h>
#include <new>

class Char_vec {
   int sz;
   char element[1];
public:
   static Char_vec* new_char_vec(int s);
   char& operator[](int i) { return element[i]; }
   // ...
};


Char_vec* Char_vec::new_char_vec(int s) {
   char *rawbytes = (char*)::operator new(sizeof(Char_vec)+s-1);
   Char_vec *vec = new(rawbytes) Char_vec;
   vec->sz = s;
   return vec;
};

int main() {
   int const N = 100;
   Char_vec &chv = *Char_vec::new_char_vec(N);
   for (int k1 = 0; k1!=N; ++k1) {
      chv[k1] = (char)k1;
   }
   for (int k2 = 0; k2!=N; ++k2) {
      if (chv[k2]!=k2) {
         std::cout << "Something is very wrong with this Char_vec!\n";
         return 1;
      }
   }
   std::cout << "Successfully filled Char_vec with values.\n";
   return 0;
}
