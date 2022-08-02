/* Code for exercise 18.10.
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
#include <list>

template<typename T>
struct in_range {
   typedef bool result_type;
   typedef T first_argument_type;
   typedef T second_argument_type;
   typedef T third_argument_type;

   bool operator()(T const &value, T const &a, T const&b) {
      return (value<b) and not (value<a);
   }
};


template<typename FO>
struct binder2_3 {
   typedef typename FO::result_type result_type;
   typedef typename FO::first_argument_type first_argument_type;
   // Constructor:
   binder2_3(FO const &fo,
             typename FO::second_argument_type const &a2,
             typename FO::third_argument_type const &a3)
      : fo_(fo), a2_(a2), a3_(a3) {}
   // Overloaded function-call operator:
   result_type operator()(first_argument_type a1) {
      return fo_(a1, a2_, a3_);
   }
private:
   FO fo_;
   typename FO::second_argument_type const a2_;
   typename FO::third_argument_type const a3_;
};


template<typename FO, typename P2, typename P3> inline
binder2_3<FO> binder3(FO const &fo, P2 const &a2, P3 const &a3) {
   return binder2_3<FO>(fo, a2, a3);
}


int main() {
   std::list<int> heights;
   int value = 31;
   std::cout << "Heights: ";
   for (int k = 0; k!=10; ++k) {
      value = value*13261%1023;
      heights.push_back(value); // Just some value
      std::cout << heights.back() << ' ';
   }
   int n_candidates = std::count_if(heights.begin(), heights.end(),
                                    binder3(in_range<int>(), 400, 600));

   std::cout << "\nIn range [400, 600]: " << n_candidates << '\n';
   return 0;
}

