/* Code for exercise 19.2.
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
#include <functional>
#include <iterator>
#include <stdio.h>


struct Sink : std::iterator<std::output_iterator_tag, void, void, void, void> {
   template<typename T> Sink& operator=(T const&) { return *this; }
   Sink& operator*() { return *this; }
   Sink const& operator*() const { return *this; }
   Sink& operator++() { return *this; } // Pre-increment
   Sink& operator++(int) { return *this; } // Post-increment
};


namespace mystd {
   template<typename In, typename F> inline
   F for_each(In begin, In end, F f) {
      std::transform(begin, end, Sink(), f);
      return f;
   } 
}

int primes[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31 };

struct Print: std::unary_function<int, int> {
   int operator()(int i) const {
      printf("%d\n", i);
      return i;
   }
};

int main() {
   mystd::for_each(&primes[0], &primes[0]+sizeof(primes)/sizeof(primes[0]),
                   Print());
   return 0;
}

