//DISPLAY 3.8 Block with a Local Variable
//Program to compute bill for either a wholesale or a retail purchase.
#include <iostream>
using namespace std;
const double TAX_RATE = 0.05; //5% sales tax.

int main( )
{
    char saleType;
    int number;
    double price, total;

    cout << "Enter price $";
    cin >> price;
    cout << "Enter number purchased: ";
    cin >> number;
    cout << "Type W if this is a wholesale purchase.\n"
         << "Type R if this is a retail purchase.\n"
         << "Then press Return.\n";
    cin >> saleType;

    if ((saleType == 'W') || (saleType == 'w'))
    {
        total = price * number;
    }
    else if ((saleType == 'R') || (saleType == 'r'))
    {
        double subtotal;
        subtotal = price * number;
        total = subtotal + subtotal * TAX_RATE;
    }
    else
    {
        cout << "Error in input.\n";
    }
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
    cout << number << " items at $" << price << endl;
    cout << "Total Bill = $" << total;
    if ((saleType == 'R') || (saleType == 'r'))
        cout << " including sales tax.\n";

    return 0;
}
