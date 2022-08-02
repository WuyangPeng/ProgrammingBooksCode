/* Code for exercise 8.10.
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

#include <limits>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <iostream>

/* If your standard librari is not in namespace std, the following
   names may clash with your library. To solve the problem you can
   add the following macros.

#define plus lplus
#define minus lminus
#define multiply lmultiply
#define divide ldivide

*/


string const op_error("arithmetic error");

double plus(double a, double b) {
   if ((b>0.0 && a>std::numeric_limits<double>::max()-b)
    || (b<0.0 && a<std::numeric_limits<double>::min()-b))
      throw std::overflow_error(op_error);
   else
      return a+b;
}

inline double minus(double a, double b) {
   return plus(a, -b);
}

double multiply(double a, double b) {
   if (std::fabs(b)>1.0
    && std::fabs(a)>std::numeric_limits<double>::max()
                    /std::fabs(b))
      throw std::overflow_error(op_error);
   double r = a*b;
   if (a!=0.0 && b!=0.0 && r==0.0)
      throw std::underflow_error(op_error);
   return r;
}

double divide(double a, double b) {
   if (std::fabs(b)<1.0
    && std::fabs(a)>std::numeric_limits<double>::max()
                   *std::fabs(b))
      throw std::overflow_error(op_error);
   double r = a/b;
   if (a!=0.0 && r==0.0)
      throw std::underflow_error(op_error);
   return r;
}

int main() {
   double big = std::numeric_limits<double>::max();
   try {
      std::cout << "big+big = ... ";
      std::cout << plus(big, big) << '\n';
   } catch (std::exception &x) {
      std::cout << "caught " << typeid(x).name()
                << " (" << x.what() << ").\n";
   }

   try {
      std::cout << "(-big)-big = ... ";
      std::cout << minus(-big, big) << '\n';
   } catch (std::exception &x) {
      std::cout << "caught " << typeid(x).name()
                << " (" << x.what() << ").\n";
   }

   try {
      std::cout << "big*big = ... ";
      std::cout << multiply(big, big) << '\n';
   } catch (std::exception &x) {
      std::cout << "caught " << typeid(x).name()
                << " (" << x.what() << ").\n";
   }

   try {
      std::cout << "1e-320/big = ... ";
      std::cout << divide(1e-320, big) << '\n';
   } catch (std::exception &x) {
      std::cout << "caught " << typeid(x).name()
                << " (" << x.what() << ").\n";
   }

}
