//DISPLAY 10.9 A SavingsAccount Class Derived from BankAccount
//Program to demonstrate the class SavingsAccount
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
    //Initializes the account balance to $0.00 and the interest rate to 0.0%.

    void set(int dollars, int cents, double rate);
    //Postcondition: The account balance has been set to $dollars.cents;
    //The interest rate has been set to rate percent.

    void set(int dollars, double rate);
    //Postcondition: The account balance has been set to $dollars.00.
    //The interest rate has been set to rate percent.

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
    double balance;
    double interestRate;

    double fraction(double percent);
    //Converts a percentage to a fraction.  For example, fraction(50.3)
    //returns 0.503.
};

BankAccount::BankAccount(int dollars, int cents, double rate)
{
    if ((dollars < 0) || (cents < 0) || (rate < 0))
    {
        cout << "Illegal values for money or interest rate.\n";
        return;
    }
    balance = dollars +0.01*cents;
    interestRate = rate;
}

BankAccount::BankAccount(int dollars, double rate)
{
    if ((dollars < 0) || (rate < 0))
    {
        cout << "Illegal values for money or interest rate.\n";
        return;
    }
    balance = dollars;
    interestRate = rate;
}

BankAccount::BankAccount( ) : balance(0), interestRate(0.0)
{
   //Body intentionally empty
}

void BankAccount::update( )
{
    balance = balance + fraction(interestRate)*balance;
}

double BankAccount::fraction(double percent_value)
{
    return (percent_value/100.0);
}



double BankAccount::getBalance( )
{
    return balance;
}

double BankAccount::getRate( )
{
    return interestRate;
}

//Uses iostream:
void BankAccount::output(ostream& outs)
{
    outs.setf(ios::fixed);
    outs.setf(ios::showpoint);
    outs.precision(2);
    outs << "Account balance $" << balance << endl;
    outs << "Interest rate " << interestRate << "%" << endl;
}

void BankAccount::set(int dollars, int cents, double rate)
{
    if ((dollars < 0) || (cents < 0) || (rate < 0))
    {
        cout << "Illegal values for money or interest rate.\n";
        return;
    }

    balance = dollars + 0.01*cents;
    interestRate = rate;
}

void BankAccount::set(int dollars, double rate)
{
    if ((dollars < 0) || (rate < 0))
    {
        cout << "Illegal values for money or interest rate.\n";
        return;
    }

    balance = dollars;
    interestRate = rate;
}


// **** Everything from Display 10.6 here except for main

class SavingsAccount : public BankAccount
{
public:
	SavingsAccount(int dollars, int cents, double rate);
	// Other constructors would go here

	void deposit(int dollars, int cents);
	// Adds $dollars.cents to the account balance

	void withdraw(int dollars, int cents);
	// Subtracts $dollars.cents from the account balance

private:
};


int main( )
{
    SavingsAccount account(100, 50, 5.5);
    account.output(cout);
    cout << endl;

    cout << "Depositing $10.25." << endl;
    account.deposit(10,25);
    account.output(cout);
    cout << endl;

    cout << "Withdrawing $11.80." << endl;
    account.withdraw(11,80);
    account.output(cout);
    cout << endl;

    return 0;
}


SavingsAccount::SavingsAccount(int dollars, int cents, double rate):
	BankAccount(dollars, cents, rate)
{
	// deliberately empty
}

void SavingsAccount::deposit(int dollars, int cents)
{
	double balance = getBalance();
	balance += dollars;
	balance += (static_cast<double>(cents) / 100);
	int newDollars = static_cast<int>(balance);
	int newCents = static_cast<int>((balance - newDollars)*100);
	set(newDollars, newCents, getRate());
}

void SavingsAccount::withdraw(int dollars, int cents)
{
	double balance = getBalance();
	balance -= dollars;
	balance -= (static_cast<double>(cents) / 100);
	int newDollars = static_cast<int>(balance);
	int newCents = static_cast<int>((balance - newDollars)*100);
	set(newDollars, newCents, getRate());
}
