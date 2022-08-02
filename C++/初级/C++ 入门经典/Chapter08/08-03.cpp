//DISPLAY 8.3 Robust Input Function
//Demonstration program for improved version of getInt.
#include <iostream>
#include <cstdlib>
#include <cctype>

void readAndClean(int& n);
//Reads a line of input. Discards all symbols except the digits. Converts
//the C string to an integer and sets n equal to the value of this integer.
void newLine( );
//Discards all the input remaining on the current input line.
//Also discards the '\n' at the end of the line.

void getInt(int& inputNumber);
//Gives inputNumber a value that the user approves of.

int main( )
{
    using namespace std;
    int inputNumber;
    getInt(inputNumber);
    cout << "Final value read in = " << inputNumber << endl;
    return 0;
}

//Uses iostream and readAndClean:
void getInt(int& inputNumber)
{
    using namespace std;
    char ans;
    do
    {
        cout << "Enter input number: ";
        readAndClean(inputNumber);
        cout << "You entered " << inputNumber
              << " Is that correct? (yes/no): ";
        cin >> ans;
        newLine( );
    } while ((ans != 'y') && (ans != 'Y'));
}
//Uses iostream, cstdlib, and cctype:
void readAndClean(int& n)

//The rest of the definition of readAndClean is given in Display 8.2.

//Uses iostream:
void newLine( )

//The rest of the definition of newLine is given in Display 8.2.