#include <iostream>
#include "Vec.h"
using namespace std;

int main()
{
    Vec<short> x(5);
    short Result;
    short i;

    for (i = 0; i < 5; i ++)
        {
        x[i] = 2 * i;
        }

    for (i = 0; i < 5; i ++)
        {
        Result = Result + x[i];
        }

    cout << Result << endl;

    return 0;
}