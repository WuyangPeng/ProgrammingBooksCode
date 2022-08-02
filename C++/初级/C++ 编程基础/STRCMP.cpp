#include <iostream>
#include "string6.h"
using std::cout;
using std::endl;

int main()
{
    string x = "x";
    string xx = "xx";
    string y = "y";
    string yy = "yy";

// testing <
    if (x < x)
        cout << "ERROR: x < x" << endl;
    else
        cout << "OKAY: x NOT < x" << endl;
    if (x < xx)
        cout << "OKAY: x < xx" << endl;
    else
        cout << "ERROR: x NOT < xx" << endl;
    if (x < y)
        cout << "OKAY: x < y" << endl;
    else
        cout << "ERROR: x NOT < y" << endl;

// testing <=
    if (x <= x)
        cout << "OKAY: x <= x" << endl;
    else
        cout << "ERROR: x NOT <= x" << endl;
    if (x <= xx)
        cout << "OKAY: x <= xx" << endl;
    else
        cout << "ERROR: x NOT <= xx" << endl;
    if (x <= y)
        cout << "OKAY: x <= y" << endl;
    else
        cout << "ERROR: x NOT <= y" << endl;

// testing >
    if (y > y)
        cout << "ERROR: y > y" << endl;
    else
        cout << "OKAY: y NOT > y" << endl;
    if (yy > y)
        cout << "OKAY: yy > y" << endl;
    else
        cout << "ERROR: yy NOT > y" << endl;
    if (y > x)
        cout << "OKAY: y > x" << endl;
    else
        cout << "ERROR: y NOT > x" << endl;

// testing >=
    if (y >= y)
        cout << "OKAY: y >= y" << endl;
    else
        cout << "ERROR: y NOT >= y" << endl;
    if (yy >= y)
        cout << "OKAY: yy >= y" << endl;
    else
        cout << "ERROR: yy NOT >= y" << endl;
    if (y >= x)
        cout << "OKAY: y >= x" << endl;
    else
        cout << "ERROR: y NOT >= x" << endl;

// testing ==
    if (x == x)
        cout << "OKAY: x == x" << endl;
    else
        cout << "ERROR: x NOT == x" << endl;
    if (x == xx)
        cout << "ERROR: x == xx" << endl;
    else
        cout << "OKAY: x NOT == xx" << endl;
    if (x == y)
        cout << "ERROR: x == y" << endl;
    else
        cout << "OKAY: x NOT == y" << endl;

// testing !=
    if (x != x)
        cout << "ERROR: x != x" << endl;
    else
        cout << "OKAY: x NOT != x" << endl;
    if (x != xx)
        cout << "OKAY: x != xx" << endl;
    else
        cout << "ERROR: x NOT != xx" << endl;
    if (x != y)
        cout << "OKAY: x != y" << endl;
    else
        cout << "ERROR: x NOT != y" << endl;

    return 0;
}

