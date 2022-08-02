#include <iostream>
#include <string>
#include "xstring.h"
using namespace std;

int main()
{
    xstring x;
    xstring y;
    xstring z;

    cout << "Please enter your first name: ";
    cin >> x;

    cout << "Please enter your last name: ";
    cin >> y;

    z = x + " ";
    z = z + y;

    cout << "Hello, " << z;

    return 0;
}
