//DISPLAY 2.1 A C++ Program
#include <iostream>
using namespace std;
int main( )
{
    int numberOfBars;
    double oneWeight, totalWeight;

    cout << "Enter the number of candy bars in a package\n";
    cout << "and the weight in ounces of one candy bar.\n";
    cout << "Then press return.\n";
    cin >> numberOfBars;
    cin >> oneWeight;

    totalWeight = oneWeight * numberOfBars;

    cout << numberOfBars << " candy bars\n";
    cout << oneWeight << " ounces each\n";
    cout << "Total weight is " << totalWeight << "ounces.\n";

    cout << "Try another brand.\n";
    cout << "Enter the number of candy bars in a package\n";
    cout << "and the weight in ounces of one candy bar.\n";
    cout << "Then press return.\n";
    cin >> numberOfBars;
    cin >> oneWeight;
    totalWeight = oneWeight * numberOfBars;

    cout << numberOfBars << " candy bars\n";
    cout << oneWeight << " ounces each\n";
    cout << "Total weight is " << totalWeight << " ounces.\n";

    cout << "Perhaps an apple would be healthier.\n";

    return 0;
}