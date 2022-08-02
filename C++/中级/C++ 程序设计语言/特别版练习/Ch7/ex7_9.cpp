/* Code for exercise 7.9.
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

#include <iostream.h>

int main(int argc, char *argv[]) {
   std::cerr << "Note: This program tends to produce non-printable output.\n"
                "      It is therefore recommended to redirect cin and cout\n"
                "      from and to files. On many systems this can be done\n"
                "      with a command like: \n"
                "         encode key <input_file >output_file\n";
   char const *key = (argc>=2)? argv[1]: "";
   size_t key_length = (argc>=2)? std::strlen(key): 1;
   char ch;
   for (std::size_t k = 0; std::cin.get(ch); k = (k+1)%key_length)
      std::cout.put(ch^key[k]);
   return 0;
}

