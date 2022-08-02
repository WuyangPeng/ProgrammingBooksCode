//DISPLAY 10.7 Alternative BankAccount Class Implementation
//Demonstrates an alternative implementation of the class BankAccount.
#include <iostream>
#include <cmath>
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
    //Initializes the account balance to $0.00 and the interest rate to 0.0%.

    void update( );
    //Postcondition: One year of simple interest has been added to the account
    //balance.

    double getBalance( );
    //Returns the current account balance.

    double getRate( );
    //Returns the current account interest rate as a percentage.

    void output(ostream& outs);
    //Precondition: If outs is a file output stream, then
    //outs has already been connected to a file.
    //Postcondition: Account balance and interest rate
    //have been written to the stream outs.
private:
    int dollarsPart;
    int centsPart;
    double interestRate;//expressed as a fraction, for example, 0.057 for 5.7%

    double fraction(double percent);
    //Converts a percentage to a fraction. For example, fraction(50.3)
    //returns 0.503.

    double percent(double fractionValue);
    //Converts a fraction to a percentage. For example, percent(0.503)
    //returns 50.3.
};

int main( )
{
    BankAccount account1(100, 2.3), account2;

    cout << "account1 initialized as follows:\n";
    account1.output(cout);
    cout << "account2 initialized as follows:\n";
    account2.output(cout);

    account1 = BankAccount(999, 99, 5.5);
    cout << "account1 reset to the following:\n";
    account1.output(cout);
    return 0;
}

BankAccount::BankAccount(int dollars, int cents, double rate)
{
    if ((dollars < 0) || (cents < 0) || (rate < 0))
    {
        cout << "Illegal values for money or interest rate.\n";
        return;
    }
    dollarsPart = dollars;
    centsPart = cents;
    interestRate = fraction(rate);
}

BankAccount::BankAccount(int dollars, double rate)
{
    if ((dollars < 0) || (rate < 0))
    {
        cout << "Illegal values for money or interest rate.\n";
        return;
    }
    dollarsPart = dollars;
    centsPart = 0;
    interestRate = fraction(rate);
}

BankAccount::BankAccount( ) : dollarsPart(0), centsPart(0), interestRate(0.0)
{
    //Body intentionally empty.
}


double BankAccount::fraction(double percentValue)
{
    return (percentValue/100.0);
}

//Uses cmath:
void BankAccount::update( )
{
    double balance = getBalance( );
    balance = balance + interestRate*balance;
    dollarsPart = floor(balance);
    centsPart = floor((balance - dollarsPart)*100);
}

double BankAccount::getBalance( )
{
    return (dollarsPart + 0.01*centsPart);
}

double BankAccount::percent(double fractionValue)
{
    return (fractionValue*100);
}

double BankAccount::getRate( )
{
    return percent(interestRate);
}

//Uses iostream:
void BankAccount::output(ostream& outs)
{
    outs.setf(ios::fixed);
    outs.setf(ios::showpoint);
    outs.precision(2);
    outs << "Account balance $" << getBalance( ) << endl;
    outs << "Interest rate " << getRate( ) << "%" << endl;
}
