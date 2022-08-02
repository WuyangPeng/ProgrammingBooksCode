/* Code for exercise 19.1.
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

#include <functional>
#include <iostream>
#include <list>

namespace mystd {
   template<typename T> inline
   void swap(T &a, T &b) {
      T tmp(a);
      a = b;
      b = tmp;
   }
}


namespace mystd {
   template<typename Bi> inline
   void reverse(Bi begin, Bi end) {
      while (begin!=end) {
         --end;
         if (begin==end)
            break;
         std::swap(*begin, *end);
         ++begin;
      }
   }
}


template<typename For>
void forward_reverse(For begin1, int len) {
   if (len>1) {
      int half_len = len/2;
      For end1 = begin1; // End of first half
      for (int k = 0; k!=half_len; ++k)
         ++end1;
      For begin2 = end1;
      if (len%2!=0) // Odd number of elements?
         ++begin2;
      std::swap_ranges(begin1, end1, begin2);
      forward_reverse(begin1, half_len);
      forward_reverse(begin2, half_len);
   }
}


int main() {
   std::list<int> L;
   int value = 31;
   std::cout << "Before reversing: ";
   for (int k = 0; k!=10; ++k) {
      value = value*13261%1023;
      L.push_back(value); // Just some value
      std::cout << L.back() << ' ';
   }

   mystd::reverse(L.begin(), L.end());
   std::cout << "\nAfter reversing: ";
   for (list<int>::iterator p = L.begin(); p!=L.end(); ++p) {
      std::cout << *p << ' ';
   }
   std::cout << '\n';

   forward_reverse(L.begin(), 10);
   std::cout << "\nAfter reversing once more: ";
   for (list<int>::iterator p = L.begin(); p!=L.end(); ++p) {
      std::cout << *p << ' ';
   }
   std::cout << '\n';

   return 0;
}

