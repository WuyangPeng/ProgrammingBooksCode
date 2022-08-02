//DISPLAY 11.8 Overloading << and >>
//Program to demonstrate the class Money.
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cctype>
using namespace std;

//Class for amounts of money in U.S. currency.
class Money
{
public:
    friend Money operator +(const Money& amount1, const Money& amount2);

    friend Money operator -(const Money& amount1, const Money& amount2);

    friend Money operator -(const Money& amount);

    friend bool operator ==(const Money& amount1, const Money& amount2);


Money(long dollars, int cents);

    Money(long dollars);

    Money( );

    double getValue( ) const;

    friend istream& operator >>(istream& ins, Money& amount);
    //Overloads the >> operator so it can be used to input values of type Money.
    //Notation for inputting negative amounts is as in -$100.00.
    //Precondition: If ins is a file input stream, then ins has already been
    //connected to a file.

    friend ostream& operator <<(ostream& outs, const Money& amount);
    //Overloads the << operator so it can be used to output values of type Money.
    //Precedes each output value of type Money with a dollar sign.
    //Precondition: If outs is a file output stream,
    //then outs has already been connected to a file.
private:
    long allCents;
};
int digitToInt(char c);
//Used in the definition of the overloaded input operator >>.
//Precondition: c is one of the digits '0' through '9'.
//Returns the integer for the digit; for example, digitToInt('3') returns 3.

int main( )
{
    Money amount;
    ifstream inStream;
    ofstream outStream;

    inStream.open("infile.dat");
    if (inStream.fail( ))
    {
        cout << "Input file opening failed.\n";
        exit(1);
    }

    outStream.open("outfile.dat");
    if (outStream.fail( ))
    {
        cout << "Output file opening failed.\n";
        exit(1);
    }


	inStream >> amount;
    outStream << amount
              << " copied from the file infile.dat.\n";
    cout << amount
         << " copied from the file infile.dat.\n";

    inStream.close( );
    outStream.close( );

    return 0;
}
//Uses iostream, cctype, cstdlib:
istream& operator >>(istream& ins, Money& amount)
{
    char oneChar, decimalPoint,
         digit1, digit2; //digits for the amount of cents
    long dollars;
    int cents;
    bool negative;//set to true if input is negative.

    ins >> oneChar;
    if (oneChar == '-')
    {
        negative = true;
        ins >> oneChar; //read '$'
    }
    else
        negative = false;
    //if input is legal, then oneChar == '$'

    ins >> dollars >> decimalPoint >> digit1 >> digit2;

    if ( oneChar != '$' || decimalPoint != '.'
         || !isdigit(digit1) || !isdigit(digit2) )
    {
        cout << "Error illegal form for money input\n";
        exit(1);
    }

    cents = digitToInt(digit1)*10 + digitToInt(digit2);

    amount.allCents = dollars*100 + cents;
    if (negative)
        amount.allCents = -amount.allCents;


return ins;
}

int digitToInt(char c)
{
    return ( static_cast<int>(c) - static_cast<int>('0') );
}

//Uses cstdlib and iostream:
ostream& operator <<(ostream& outs, const Money& amount)
{
    long positiveCents, dollars, cents;
    positiveCents = labs(amount.allCents);
    dollars = positiveCents/100;
    cents = positiveCents%100;

    if (amount.allCents < 0)
        outs << "-$" << dollars << '.';
    else
        outs << "$" << dollars << '.';

    if (cents < 10)
        outs << '0';
    outs << cents;

    return outs;
}

//The definitions of the member functions and other overloaded operators go here.
//See Display 11.3, 11.4, 11.5, and 11.6 for the definitions.
