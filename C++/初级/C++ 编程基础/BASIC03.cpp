#include <iostream>
using namespace std;

int main()
{
    short balance;

    cout << "Please enter your bank balance: ";
    cin >> balance;

    if (balance < 10000)
        cout << "Please remit $20 service charge." << endl;
    else
        cout << "Have a nice day!" << endl;

    return 0;
}
