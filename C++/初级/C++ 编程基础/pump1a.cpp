#include <iostream>
using namespace std;

int main()
{
    short CurrentWeight;
    short HighestWeight;
    short SecondHighestWeight;

    cout << "Please enter the first weight: ";
    cin >> CurrentWeight;
    HighestWeight = CurrentWeight;
    SecondHighestWeight = 0;
    cout << "Current weight " << CurrentWeight << endl;
    cout << "Highest weight " << HighestWeight << endl;

    while (CurrentWeight > 0)
        {
        cout << "Please enter the next weight: ";
        cin >> CurrentWeight;
        if (CurrentWeight > HighestWeight)
            {
            SecondHighestWeight = HighestWeight;
            HighestWeight = CurrentWeight;
            }
        cout << "Current weight " << CurrentWeight << endl;
        cout << "Highest weight " << HighestWeight << endl;
        cout << "Second highest weight " << SecondHighestWeight << endl;
        }

    return 0;
}

