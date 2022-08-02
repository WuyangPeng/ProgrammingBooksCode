/*
 * This file contains code from "C++ Primer, Fourth Edition", by Stanley B.
 * Lippman, Jose Lajoie, and Barbara E. Moo, and is covered under the
 * copyright and warranty notices given in that book:
 * 
 * "Copyright (c) 2005 by Objectwrite, Inc., Jose Lajoie, and Barbara E. Moo."
 * 
 * 
 * "The authors and publisher have taken care in the preparation of this book,
 * but make no expressed or implied warranty of any kind and assume no
 * responsibility for errors or omissions. No liability is assumed for
 * incidental or consequential damages in connection with or arising out of the
 * use of the information or programs contained herein."
 * 
 * Permission is granted for this code to be used for educational purposes in
 * association with the book, given proper citation if and when posted or
 * reproduced.Any commercial use of this code requires the explicit written
 * permission of the publisher, Addison-Wesley Professional, a division of
 * Pearson Education, Inc. Send your request for permission, stating clearly
 * what code you would like to use, and in what specific way, to the following
 * address: 
 * 
 * 	Pearson Education, Inc.
 * 	Rights and Contracts Department
 * 	75 Arlington Street, Suite 300
 * 	Boston, MA 02216
 * 	Fax: (617) 848-7047
*/ 

#include <string>
#include <iostream>
using std::cout; using std::endl;
using std::string;

char *cp = "Hiya";            // null-terminated array
char c_array[] = "World!!!!"; // null-terminated
char no_null[] = {'H', 'i'};  // not null-terminated

string s1(cp);             // s1 == "Hiya"
string s2(c_array, 5);     // s2 == "World"
string s3(c_array + 5, 4); // s3 == "!!!!"
string s4(no_null);        // runtime error: no_null not null-terminated
string s5(no_null, 2);     // ok: s5 == "Hi"

    string s6(s1, 2);    // s6 == "ya"

    string s7(s1, 0, 2); // s7 == "Hi"

    string s8(s1, 0, 8); // s8 == "Hiya"

int main()
{
    cout << s1 << '\n' << s2 << '\n'
         << s3 << '\n' << s5 << '\n'
         << s6 << '\n' << s7 << endl;

{
    string s1;           // s1 is the empty string
    string s2(5, 'a');   // s2 == "aaaaa"
    string s3(s2);       // s3 is a copy of s2
    string s4(s3.begin(), 
              s3.begin() + s3.size() / 2);  // s4 == "aa"
    cout << s1 << '\n' << s2 << '\n'
         << s3 << '\n' << s4 << endl;
}

return 0;
}
