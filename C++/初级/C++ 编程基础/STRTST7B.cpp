#include <iostream>
#include "string7.h"

int main()
{
    string x = "purple";
    string y = "A purple couch";
    short where;

    where = y.find_nocase(x);
    cout << "The string " << x << 
        " can be found starting at position " <<
        where << " in the string " << endl;
    cout << y << "." << endl;

    where = x.find_nocase("rp");
    cout << "The string 'rp' can be found starting at position " << 
        where << " in the string " << x << "." << endl;

    where = x.find_nocase("rpx");
    cout << "The string 'rpx' can be found starting at position " << 
        where << " in the string " << x << "." << endl;

    return 0;
}
