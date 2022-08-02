#include <iostream>
#include "Vec.h"
using namespace std;

int main()
{
    Vec<short> x(4);
    short Result;
    short i;

    x[0] = 3;
    for (i = 1; i < 4; i ++)
        x[i] = x[i-1] * 2;

    Result = 0;
    for (i = 0; i < 4; i ++)
        Result = Result + x[i];

    cout << Result << endl;

    return 0;
}