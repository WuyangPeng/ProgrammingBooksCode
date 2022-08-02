//DISPLAY 2.17 Comments and Named Constants
//File Name: health.cpp (Your system may require some suffix other than cpp.)
//Author: Your Name Goes Here.
//Email Address: you@yourmachine.bla.bla
//Assignment Number: 2
//Description: Program to determine if the user is ill.
//Last Changed: September 23, 2017

#include <iostream>
using namespace std;
int main( )
{
    const double NORMAL = 98.6;//degrees Fahrenheit
    double temperature;

    cout << "Enter your temperature: ";
    cin >> temperature;

    if (temperature > NORMAL)
    {
        cout << "You have a fever.\n";
        cout << "Drink lots of liquids and get to bed.\n";
    }
        cout << "Go study.\n";
    }

    return 0;
}
