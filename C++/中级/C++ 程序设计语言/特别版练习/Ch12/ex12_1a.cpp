/* Code for exercise 12.1.
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

class base {
public:
   virtual void iam() { std::cout << "base\n"; }
};

struct Northpole: public base {
   virtual void iam() { std::cout << "Northpole.\n"; }
};

struct Southpole: public base {
   virtual void iam() { std::cout << "Southpole.\n"; }
};

int main() {
   Northpole NP;
   Southpole SP;
   NP.iam();
   SP.iam();
   base *pole1= &NP, *pole2 = &SP;
   pole1->iam(); // or (*pole1).iam()
   (*pole2).iam(); // or pole2->iam()
   return 0;
}

