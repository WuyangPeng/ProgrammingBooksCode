//DISPLAY 11.5 Overloading Operators
//Program to demonstrate the class Money. (This is an improved version of
//the class Money that we gave in Display 11.3 and rewrote in Display 11.4.)
#include <iostream>
#include <cstdlib>
#include <cctype>
using namespace std;

//Class for amounts of money in U.S. currency.
class Money
{
public:
    friend Money operator +(const Money& amount1, const Money& amount2);
    //Precondition: amount1 and amount2 have been given values.
    //Returns the sum of the values of amount1 and amount2.

    friend bool operator ==(const Money& amount1, const Money& amount2);
    //Precondition: amount1 and amount2 have been given values.
    //Returns true if amount1 and amount2 have the same value;
    //otherwise, returns false.

    Money(long dollars, int cents);

    Money(long dollars);

    Money( );

    double getValue( ) const;

    void input(istream& ins);

    void output(ostream& outs) const;
private:
    long allCents;
};

//Any extra function declarations from Display 11.3 go here.

int main( )
{
    Money cost(1, 50), tax(0, 15), total;
    total = cost + tax;

    cout << "cost = ";
    cost.output(cout);
    cout << endl;


	cout << "tax = ";
    tax.output(cout);
    cout << endl;
    cout << "total bill = ";
    total.output(cout);
    cout << endl;
    if (cost == tax)
        cout << "Move to another state.\n";
    else
        cout << "Things seem normal.\n";
    return 0;
}

Money operator +(const Money& amount1, const Money& amount2)
{
    Money temp;
    temp.allCents = amount1.allCents + amount2.allCents;
    return temp;
}

bool operator ==(const Money& amount1, const Money& amount2)
{
    return (amount1.allCents == amount2.allCents);
}


     //The definitions of the member functions are the same as in
//Display 11.3 except that const is added to the function headings
//in various places so that the function headings match the function
//declarations in the preceding class definition. No other changes
//are needed in the member function definitions. The bodies of the
//member function definitions are identical to those in Display 11.3.