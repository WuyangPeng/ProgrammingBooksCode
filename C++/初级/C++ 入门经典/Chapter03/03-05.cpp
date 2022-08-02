//DISPLAY 3.5 Multiway if-else Statement
//Program to compute state income tax.
#include <iostream>
using namespace std;


//This program outputs the amount of state income tax due computed
//as follows: no tax on income up to $15,000; 5% on income between
//$15,001 and $25,000; 10% on income over $25,000.


int main( )
{
    int netIncome;
    double taxBill;
    double fivePercentTax, tenPercentTax;


    cout << "Enter net income (rounded to whole dollars) $";
    cin >> netIncome;

 	if (netIncome <= 15000)
        taxBill = 0;
    else if ((netIncome > 15000) && (netIncome <= 25000))
        //5% of amount over $15,000
        taxBill = (0.05*(netIncome - 15000));
    else //netIncome > $25,000
    {
        //fivePercentTax = 5% of income from $15,000 to $25,000.
        fivePercentTax = 0.05*10000;
        //tenPercentTax = 10% of income over $25,000.
        tenPercentTax = 0.10*(netIncome - 25000);
        taxBill = (fivePercentTax + tenPercentTax);
    }

    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
    cout << "Net income = $" << netIncome << endl
         << "Tax bill = $" << taxBill << endl;

    return 0;
}
