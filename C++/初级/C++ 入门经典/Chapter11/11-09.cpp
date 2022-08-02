//DISPLAY 11.9 Program Using an Array of the Money Object
//This is the definition for the class Money.
//Values of this type are amounts of money in U.S. currency.
#include <iostream>
using namespace std;


  class Money
  {
  public:
     friend Money operator +(const Money& amount1, const Money& amount2);
     //Returns the sum of the values of amount1 and amount2.

     friend Money operator -(const Money& amount1, const Money& amount2);
     //Returns amount 1 minus amount2.

     friend Money operator -(const Money& amount);
     //Returns the negative of the value of amount.

     friend bool operator ==(const Money& amount1, const Money& amount2);
     //Returns true if amount1 and amount2 have the same value; false otherwise.

     friend bool operator < (const Money& amount1, const Money& amount2);
     //Returns true if amount1 is less than amount2; false otherwise.

     Money(long dollars, int cents);
     //Initializes the object so its value represents an amount with
     //the dollars and cents given by the arguments. If the amount
     //is negative, then both dollars and cents should be negative.

     Money(long dollars);
     //Initializes the object so its value represents $dollars.00.

     Money( );
     //Initializes the object so its value represents $0.00.

     double getValue( ) const;
     //Returns the amount of money recorded in the data portion of the calling
     //object.

     friend istream& operator >>(istream& ins, Money& amount);
     //Overloads the >> operator so it can be used to input values of type
     //Money. Notation for inputting negative amounts is as in -$100.00.
     //Precondition: If ins is a file input stream, then ins has already been
     //connected to a file.


friend ostream& operator <<(ostream& outs, const Money& amount);
     //Overloads the << operator so it can be used to output values of type
     //Money. Precedes each output value of type Money with a dollar sign.
     //Precondition: If outs is a file output stream, then outs has already been
     //connected to a file.
  private:
     long allCents;
  };

//Reads in 5 amounts of money and shows how much each
//amount differs from the largest amount.

int main( )
{
    Money amount[5], max;
    int i;

    cout << "Enter 5 amounts of money:\n";
    cin >> amount[0];
    max = amount[0];
    for (i = 1; i < 5; i++)
    {
        cin >> amount[i];
        if (max < amount[i])
            max = amount[i];
        //max is the largest of amount[0],..., amount[i].
    }

    Money difference[5];
    for (i = 0; i < 5; i++)
        difference[i] = max - amount[i];

    cout << "The highest amount is " << max << endl;
    cout << "The amounts and their\n"
         << "differences from the largest are:\n";
    for (i = 0; i < 5; i++)
    {
        cout << amount[i] << " off by "
             << difference[i] << endl;
    }

    return 0;
}

