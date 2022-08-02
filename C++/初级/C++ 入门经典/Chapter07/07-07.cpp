//DISPLAY 7.7 The Function scale
//Demonstration program for the function scale.
#include <iostream>
#include <cmath>

void scale(int a[], int size);
//Precondition: a[0] through a[size-1] each has a nonnegative value.
//Postcondition: a[i] has been changed to the number of 1000s (rounded to
//an integer) that were originally in a[i], for all i such that 0 <= i <= size -1.

int roundNum(double number);
//Precondition: number >= 0.
//Returns number rounded to the nearest integer.

int main( )
{
    using namespace std;
    int someArray[4], index;

    cout << "Enter 4 numbers to scale: ";
    for (index = 0; index < 4; index++)
        cin >> someArray[index];

    scale(someArray, 4);

    cout << "Values scaled to the number of 1000s are: ";
    for (index = 0; index < 4; index++)
        cout << someArray[index] << " ";
    cout << endl;

    return 0;
}

void scale(int a[], int size)
{
    for (int index = 0; index < size; index++)
        a[index] = roundNum(a[index]/1000.0);
}

//Uses cmath:
int roundNum(double number)
{
    using namespace std;
    return static_cast<int>(floor(number + 0.5));
}

