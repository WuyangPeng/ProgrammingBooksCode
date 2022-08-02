/* Code for exercise 11.1.
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

#include <iostream>

struct X {
   int I;
   X() {}
   X(int i): I(i) { std::cerr << "X::X(int)\n"; }
   X operator+(int i) {
      std::cerr << "X::operator+(int)\n";
      X r;
      r.I = I+i;
      return r;
   }
};

struct Y {
   int I;
   Y() {}
   Y(X x): I(x.I) { std::cerr << "Y::Y(X)\n"; }
   Y operator+(X x) {
      Y r;
      r.I = I+x.I;
      return r;
   }
   operator int() { std::cerr << "Y::operator int()\n"; return I; }
};

extern X operator*(X x, Y y) {
   X r;
   r.I = x.I+y.I;
   return r;
}

extern int f(X x) {
   return x.I;
}

X x = 1;
Y y = x;
int i = 2;

int main() {
   cout << "i+10 = ... " << i+10 << '\n' << std::endl; // No conversion needed

#if defined COMPILE_ERRORS
   y+10; // Error: ambiguous!
      // y.operator int()+10 or y+X(10)
   y+10*y; // Error: ambiguous again!
      // y+X(10*y.operator int()) or y+X(10)*y
#endif

	std::cout << "x+y+i = ... " << (x+y+i).I << '\n' << std::endl;
#if 0
   (x+y.operator int())+i; // Uses X::operator+(int) twice;
                           // result has type X
#endif

   std::cout << "x*x+i = ... " << (x*x+i).I << '\n' << std::endl;
#if 0
   x*Y(x)+X(i); // Result has type X
#endif

   std::cout << "f(7) = ... " << f(7) << '\n' << std::endl;
#if 0
   f(X(7));
#endif

#if defined COMPILE_ERRORS
   f(y); // Error: no valid implicit conversion from Y to X
#endif

   std::cout << "y+y = ... " << y+y << '\n' << std::endl;
#if 0
   y.operator int()+y.operator int(); // Result has type int
#endif

   std::cout << "106+y = ... " << 106+y << '\n' << std::endl;
#if 0
   106+y.operator int(); // Result has type int
#endif
};

