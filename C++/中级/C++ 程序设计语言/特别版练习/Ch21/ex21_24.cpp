/* Code for exercise 21.24.
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
#include <vector>

struct ModifyIOXState {
   ModifyIOXState(std::basic_ios<char> &stream, std::ios_base::iostate state)
      : stream_(stream), old_state_(stream.exceptions()) {
      stream.exceptions(state);
   }
   ~ModifyIOXState() { stream_.exceptions(old_state_); }
private:
   std::basic_ios<char> &stream_;
   std::ios_base::iostate old_state_;
};

void readints(std::vector<int> &s) { // Still not our favorite
                                     // style, but better hand-
                                     // ling of exceptions
   ModifyIOXState throw_on_eof(std::cin, std::ios_base::eofbit);
   for (;;)
      try {
         int i;
         std::cin >> i;
std::cout << i;
         s.push_back(i);
      } catch (std::ios_base::failure &x) {
         // OK: end of file reached
         std::cout << "Note: end-of-file reached!\n";
      }
}


int main() {
   std::vector<int> large(1000);
   try {
      readints(large);
   } catch(...) {
      std::cerr << "Caught unknown exception in main()!\n";
   }
   return 0;
}

