/* Code for exercise 10.15.
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

int main() {
   std::cout << "Hello, world!\n";
}

struct GlobalBracket {
   GlobalBracket() { std::cout << "Initialize\n"; }
   ~GlobalBracket() { std::cout << "Clean up\n"; }
} global_bracket_variable;

