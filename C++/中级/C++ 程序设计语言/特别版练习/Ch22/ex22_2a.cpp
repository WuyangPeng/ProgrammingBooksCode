/* Code for exercise 22.2.
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
#include <iostream>
#include <valarray>

template<typename T, typename F>
void apply(std::valarray<T> &a, F f) {
   for (std::size_t k = 0; k!=a.size(); ++k)
      a[k] = f(a[k]);
}


struct Sqr {
   double operator()(double a) { return a*a; }
};

double primes[] = { 2.0, 3.0, 5.0, 7.0, 11.0, 13.0 };

int main() {
   std::valarray<double> va(primes, sizeof(primes)/sizeof(primes[0]));
   std::cout << "va = [ ";
   std::copy(&va[0U], &va[0U]+va.size(),
             std::ostream_iterator<double, char>(std::cout, " "));
   std::cout << "]\n";
   apply(va, Sqr());
   std::cout << "apply(va, Sqr())\n";
   std::cout << "va = [ ";
   std::copy(&va[0U], &va[0U]+va.size(),
             std::ostream_iterator<double, char>(std::cout, " "));
   std::cout << "]\n";
   return 0;
}

