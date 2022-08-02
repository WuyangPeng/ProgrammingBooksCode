#include <iostream>
using namespace std;

short i;

short Calc(short x, short y)
{
static short j = 0;

    cout << "The value of j in Calc is: " << j << endl;

    i ++;

    j = x + y + j;

    return j;
}

int main()
{
    short j;

    for (i = 0; i < 5; i ++)
        {
        j = Calc(i + 5, i * 2) + 7;
        cout << "The value of j in main is: " << j << endl;
        }

    return 0;
}
