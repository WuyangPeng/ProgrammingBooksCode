#include <iostream>
using namespace std;

int main()
{
    short CurrentWeight;
    short HighestWeight;

    cout << "Please enter the first weight: ";
    cin >> CurrentWeight;
    HighestWeight = CurrentWeight;
    cout << "Current weight " << CurrentWeight << endl;
    cout << "Highest weight " << HighestWeight << endl;

    while (CurrentWeight > 0)
        {
        cout << "Please enter the next weight: ";
        cin >> CurrentWeight;
        if (CurrentWeight > HighestWeight)
            HighestWeight = CurrentWeight;
        cout << "Current weight " << CurrentWeight << endl;
        cout << "Highest weight " << HighestWeight << endl;
        }

    return 0;
}

