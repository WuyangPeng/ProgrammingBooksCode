/* Code for exercise 18.1.
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
#include <vector>

template<typename R, typename T, typename P1>
struct mem_fun1_ref_t {
   typedef R return_type;
   typedef T first_argument_type;
   typedef P1 second_argument_type;
   typedef R (T::*PMF)(P1); // PMF is a pointer-to-member-
                            // function type (§15.5)
   explicit mem_fun1_ref_t(PMF pmf): pmf_(pmf) {}
   R operator()(T &obj, P1 arg) const
      { return (obj.*pmf_)(arg); }
private:
   PMF pmf_;
};



template<typename R, typename T, typename P1>
mem_fun1_ref_t<R, T, P1> mem_fun_ref(R (T::*pmf)(P1)) {
   return mem_fun1_ref_t<R, T, P1>(pmf);
}

struct Box {
   Box rotate(int i) {
      std::cout << "Rotate " << i << " degrees\n";
      return *this;
   }
};


int main() {
   vector<Box> squares(10);
   vector<int> angles(10);
   for (int k = 0; k!=10; ++k) { angles[k] = k*k; }
#if 0
   transform(squares.begin(), squares.end(),
             angles.begin(), squares.begin(),
             mem_fun1_ref_t<Box, Box, int>(&Box::rotate));
#else // same thing
   transform(squares.begin(), squares.end(), angles.begin(),
             squares.begin(), mem_fun_ref(&Box::rotate));
#endif
   return 0;
}

