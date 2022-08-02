#include <iostream>
using std::cout;
using std::endl;
#include "string4.h"

int main()
{
    short len;
    string n("Test");

    len = n.GetLength();

    cout << "The string has " << len << " characters." << endl;

    return 0;
}