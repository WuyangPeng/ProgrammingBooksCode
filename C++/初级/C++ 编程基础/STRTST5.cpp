#include <iostream>
#include "string5.h"

using std::cout;
using std::endl;

int main()
{
    string x;
    string y;

    x = "post";
    y = "poster";

    if (x < y)
      cout << x << " comes before " << y << endl;
    else
      cout << x << " doesn't come before " << y << endl;

    return 0;
}
