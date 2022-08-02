#include <iostream>
using namespace std;

short Average(short First, short Second)
{
    short Result;

    Result = (First + Second) / 2;

    return Result;
}

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

    AverageWeight = Average(FirstWeight, SecondWeight);

    cout << "Please type in the first age: ";
    cin >> FirstAge;

    cout << "Please type in the second age: ";
    cin >> SecondAge;

    AverageAge = Average(FirstAge, SecondAge);

    cout << "The average weight was: " << AverageWeight << endl;
    cout << "The average age was: " << AverageAge << endl;

    return 0;
}