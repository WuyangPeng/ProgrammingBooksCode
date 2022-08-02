#include <iostream>
using namespace std;

int main()
{
    short FirstWeight;
    short SecondWeight;
    short FirstAge;
    short SecondAge;
    short AverageWeight;
    short AverageAge;

    cout << "Please type in the first weight: ";
    cin >> FirstWeight;

    cout << "Please type in the second weight: ";
    cin >> SecondWeight;

    AverageWeight = (FirstWeight + SecondWeight) / 2;

    cout << "Please type in the first age: ";
    cin >> FirstAge;

    cout << "Please type in the second age: ";
    cin >> SecondAge;

    AverageAge = (FirstAge + SecondAge) / 2;

    cout << "The average weight was: " << AverageWeight << endl;
    cout << "The average age was: " << AverageAge << endl;

    return 0;
}
