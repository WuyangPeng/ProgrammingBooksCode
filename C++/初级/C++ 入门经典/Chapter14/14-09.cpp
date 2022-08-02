//DISPLAY 14.9 A Recursive Member Function
//Program to demonstrate the recursive member function update(years).
#include <iostream>
using namespace std;

//Class for a bank account:
class BankAccount
{
public:
    BankAccount(int dollars, int cents, double rate);
    //Initializes the account balance to $dollars.cents and
    //initializes the interest rate to rate percent.

    BankAccount(int dollars, double rate);
    //Initializes the account balance to $dollars.00 and
    //initializes the interest rate to rate percent.

    BankAccount( );
    //Initializes the account balance to $0.00 and
    //initializes the interest rate to 0.0%.

    void update( );
    //Postcondition: One year of simple interest
    //has been added to the account balance.

    void update(int years);
    //Postcondition: Interest for the number of years given has been added to the
    //account balance. Interest is compounded annually.

    double getBalance( );
    //Returns the current account balance.

    double getRate( );
    //Returns the current account interest rate as a percentage.

    void output(ostream& outs);
    //Precondition: If outs is a file output stream, then outs has already
    //been connected to a file.
    //Postcondition: Balance & interest rate have been written to the stream outs.
private:
    double balance;
    double interestRate;
    double fraction(double percent); //Converts a percentage to a fraction.
};
int main( )
{
    BankAccount yourAccount(100, 5);
    yourAccount.update(10);
    cout.setf(ios::fixed);

    cout.setf(ios::showpoint);
    cout.precision(2);
    cout << "If you deposit $100.00 at 5% interest, then\n"
         << "in ten years your account will be worth $"
         << yourAccount.getBalance( ) << endl;
    return 0;
}

void BankAccount::update( )
{
    balance = balance + fraction(interestRate)*balance;
}

void BankAccount::update(int years)
{
    if (years == 1)
    {
        update( );
    }
    else if (years > 1)
    {
        update(years - 1);
        update( );
    }
}
