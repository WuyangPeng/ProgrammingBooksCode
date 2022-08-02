/* Code for exercise 25.19.
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
#include <iostream>

template<typename F, typename G>
struct FunctionComposition {
   typedef typename F::result_type result_type;
   typedef typename G::argument_type argument_type;
   FunctionComposition(F const &f, G const &g) : f_(f), g_(g) {}
   result_type operator()(argument_type x) { return f_(g_(x)); }
private:
   F f_;
   G g_;
};


template<typename F, typename G>
FunctionComposition<F, G> compose(F const &f, G const &g) {
   return FunctionComposition<F, G>(f, g);
}


struct Sqr: std::unary_function<int, int> {
   int operator()(int i) const { return i*i; }
};


struct SubOne: std::unary_function<int, int> {
   int operator()(int i) const { return i-1; }
};


int main() {
   int primes[] = { 2, 3, 5, 7, 11, 13 };
   std::cout << "Primes: ";
   std::copy(&primes[0], &primes[0]+sizeof(primes)/sizeof(primes[0]),
             std::ostream_iterator<int, char>(std::cout, " "));
   std::cout << "\nAfter compose(Sqr(), SubOne()): ";
   std::transform(&primes[0], &primes[0]+sizeof(primes)/sizeof(primes[0]),
                  std::ostream_iterator<int, char>(std::cout, " "),
                  compose(Sqr(), SubOne()));
   std::cout << "\nAfter compose(SubOne(), Sqr()): ";
   std::transform(&primes[0], &primes[0]+sizeof(primes)/sizeof(primes[0]),
                  std::ostream_iterator<int, char>(std::cout, " "),
                  compose(SubOne(), Sqr()));
   std::cout << '\n';
   return 0;
}

