//DISPLAY 5.2 void Functions
//Program to convert a Fahrenheit temperature to a Celsius temperature.
#include <iostream>

void initializeScreen( );
//Separates current output from
//the output of the previously run program.

double celsius(double fahrenheit);
//Converts a Fahrenheit temperature
//to a Celsius temperature.

void showResults(double fDegrees, double cDegrees);
//Displays output. Assumes that cDegrees
//Celsius is equivalent to fDegrees Fahrenheit.

int main( )
{
    using namespace std;
    double fTemperature, cTemperature;

    initializeScreen( );
    cout << "I will convert a Fahrenheit temperature"
         << " to Celsius.\n"
         << "Enter a temperature in Fahrenheit: ";
    cin >> fTemperature;

    cTemperature = celsius(fTemperature);

    showResults(fTemperature, cTemperature);
    return 0;
}

//Definition uses iostream:
void initializeScreen( )
{
    using namespace std;
    cout << endl;
    return;
}
double celsius(double fahrenheit)
{
    return ((5.0/9.0)*(fahrenheit - 32));
}
//Definition uses iostream:
void showResults(double fDegrees, double cDegrees)
{
    using namespace std;
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(1);
    cout << fDegrees
         << " degrees Fahrenheit is equivalent to\n"
         << cDegrees << " degrees Celsius.\n";
    return;
}
