/* Code for exercise 6.22.
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

using std::cin;

enum Context { c_comment, cpp_comment,
               string_literal, char_literal, file_end };

void handle_c_comment() {
   char ch;
   while (cin.get(ch)) {
      if (ch=='*') {
         // Skip additional asterisks:
         while(cin.get(ch) && ch=='*');
         if (ch=='/')
            break;
      }
   }
}

void handle_cpp_comment() {
   // Skip until end-of-line:
   char ch;
   while (cin.get(ch) && ch!='\n');
   cout << '\n';
}

void handle_literal(char delimiter) {
   cout << delimiter; // Read left delimiter
   char ch;
   while (cin.get(ch)) {
      cout << ch;
      if (ch==delimiter) // Right delimiter found?
         break;
      else if (ch=='\\') // Next character passed unmodified
         cin.get(ch) && cout << ch;
   }
}

Context handle_code() {
   char ch;
   while (cin.get(ch)) {
      switch (ch) {
         case '/':
            if (!cin.get(ch)) { // This would in fact be
               cout << '/';       //  erroneous C++ code
               return file_end;
            } else {
               if (ch=='*')
                  return c_comment;
               else if (ch=='/')
                  return cpp_comment;
               else {
                  cout << '/';
                  cin.putback(ch);
                  break;
               }
            }
         case '\"': return string_literal;
         case '\'': return char_literal;
         default: cout << ch;
      }
   }
   return file_end;
}

int main(int argc, char *argv[]) {
   if (argc>1) {
      cerr << "This program takes no arguments.\n";
      return -1;
   } else {
      Context context;
      while ((context = handle_code())!=file_end)
         switch(context) {
            case c_comment:
               handle_c_comment();
               break;
            case cpp_comment:
               handle_cpp_comment();
               break;
            case string_literal:
               handle_literal('\"');
               break;
            case char_literal:
               handle_literal('\'');
               break;
         }
      return 0;
   }
}

