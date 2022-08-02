//DISPLAY 3.4 The Importance of Braces
//Illustrates the importance of using braces in if-else statements.
#include <iostream>
using namespace std;
int main( )
{
    double fuelGaugeReading;

    cout << "Enter fuel gauge reading: ";
    cin >> fuelGaugeReading;

    cout << "First with braces:\n";
    if (fuelGaugeReading < 0.75)
    {
        if (fuelGaugeReading < 0.25)
            cout << "Fuel very low. Caution!\n";
    }
    else
    {
        cout << "Fuel over 3/4. Dont stop now!\n";
    }

    cout << "Now without braces:\n";
    if (fuelGaugeReading < 0.75)
        if (fuelGaugeReading < 0.25)
            cout << "Fuel very low. Caution!\n";
    else
        cout << "Fuel over 3/4. Don't stop now!\n";

    return 0;
}
