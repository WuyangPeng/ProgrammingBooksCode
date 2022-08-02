/* The following code example is taken from the book
 * "The C++ Standard Library - A Tutorial and Reference, 2nd Edition"
 * by Nicolai M. Josuttis, Addison-Wesley, 2012
 *
 * (C) Copyright Nicolai M. Josuttis 2012.
 * Permission to copy, use, modify, sell and distribute this software
 * is granted provided this copyright notice appears in all copies.
 * This software is provided "as is" without express or implied
 * warranty, and with no claim as to its suitability for any purpose.
 */
#include <regex>
#include <iostream>
#include "regexexception.hpp"
using namespace std;

int main()
{
  try {
    // initialize regular expression with invalid syntax:
    regex pat ("\\\\.*index\\{([^}]*)\\}",
               regex_constants::grep|regex_constants::icase);
    //...
  }
  catch (const regex_error& e) {
        cerr << "regex_error: \n"
             << " what(): " << e.what() << "\n"
             << " code(): " << regexCode(e.code()) << endl;
  }
}
