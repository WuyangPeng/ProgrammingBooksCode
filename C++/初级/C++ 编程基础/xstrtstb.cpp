#include <iostream>
#include <string>
#include "xstring.h"
using namespace std;

int main()
{
    xstring x = "purple";
    xstring y = "A Purple couch";
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
