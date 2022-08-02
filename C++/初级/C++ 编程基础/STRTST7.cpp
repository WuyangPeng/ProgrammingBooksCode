#include <iostream>
#include "string7.h"

int main()
{
    string x;
    string y;
    string z;
    short where;

    x = "post";
    y = "poster";

    if (x < y)
      cout << x << " comes before " << y << endl;
    else
      cout << x << " doesn't come before " << y << endl;

    where = y.find_nocase(x);
    cout << "string x starts at position " << 
        where << " in string y." << endl;

    where = x.find_nocase("st");
    cout << "string 'st' starts at position " << 
        where << " in string y." << endl;

    where = x.find_nocase("str");
    cout << "string 'str' starts at position " << 
        where << " in string y." << endl;

    cout << endl;

    cout << "Please enter your first name: ";
    cin >> x;

    cout << "Please enter your last name: ";
    cin >> y;

    z = x + " " + y;

    cout << "Hello, " << z << endl;

    return 0;
}
