//DISPLAY 14.1 A Recursive Output Function
//Program to demonstrate the recursive function writeVertical.
#include <iostream>
using namespace std;

void writeVertical(int n);
//Precondition: n >= 0.
//Postcondition: The number n is written to the screen vertically
//with each digit on a separate line.

int main( )
{
    cout << "writeVertical(3):" << endl;
    writeVertical(3);

    cout << "writeVertical(12):" << endl;
    writeVertical(12);

    cout << "writeVertical(123):" << endl;
    writeVertical(123);

    return 0;
}

//uses iostream:
void writeVertical(int n)
{
    if (n < 10)
    {
        cout << n << endl;
    }
    else //n is two or more digits long:
    {
        writeVertical(n/10);
        cout << (n%10) << endl;
    }
}
