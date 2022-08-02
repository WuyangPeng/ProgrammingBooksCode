/* Code for exercise 11.21.
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

#include <stdio.h>
#include <math.h>

struct Index {
   Index(double p): p_(p) {}
   Index const& operator*() const { return *this; }
   double value() const { return p_; }
private:
   double p_;
};

double mypow(double b, Index p) {
   return pow(b, p.value());
}

double operator*(double a, Index const &b) {
   return mypow(a, b);
}

int main() {
   printf("2.3**Index(3.0) = %f\n", 2.3**Index(3.0));
   return 0;
}

