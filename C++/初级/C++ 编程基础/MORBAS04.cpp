#include <iostream>
using namespace std;

int main()
{
    short weight;
    short total;

    cout << "Please type in your weight, typing 0 to end:";
    cin >> weight;

    total = weight;

    while (weight > 0)
        {
        cout << "Please type in your weight, typing 0 to end:";
        cin >> weight;
        total = total + weight;
        }
 
    cout << "The total is: " << total << endl;
    return 0;
}
