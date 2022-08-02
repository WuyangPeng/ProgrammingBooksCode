#include <iostream>
using namespace std;

int main()
{
    short n;

    cout << "Excluding yourself, please type the ";
    cout << "number of guests in your dinner party.\n";

    cin >> n;

    if (n>20)
        cout << "Sorry, your party is too large. ";
    else
        cout << "A table for " << n+1 << " is ready. ";

    return 0;
}