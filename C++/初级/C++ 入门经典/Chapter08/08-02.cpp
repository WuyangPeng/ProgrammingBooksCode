//DISPLAY 8.2 C Strings to Integers
//Demonstrates the function readAndClean.
#include <iostream>
#include <cstdlib>
#include <cctype>

void readAndClean(int& n);
//Reads a line of input. Discards all symbols except the digits. Converts
//the C string to an integer and sets n equal to the value of this integer.

void newLine( );
//Discards all the input remaining on the current input line.
//Also discards the '\n' at the end of the line.

int main( )
{
    using namespace std;
    int n;
    char ans;
    do
    {
        cout << "Enter an integer and press Return: ";
        readAndClean(n);
        cout << "That string converts to the integer " << n << endl;
        cout << "Again? (yes/no): ";
        cin >> ans;
        newLine( );
    } while ( (ans != 'n') && (ans != 'N') );
    return 0;
}
//Uses iostream, cstdlib, and cctype:
void readAndClean(int& n)
{
    using namespace std;
    const int ARRAY_SIZE = 6;
    char digitString[ARRAY_SIZE];

    char next;
    cin.get(next);
    int index = 0;
    while (next != '\n')
    {
        if ( (isdigit(next)) && (index < ARRAY_SIZE - 1) )
        {
            digitString[index] = next;
            index++;
        }
        cin.get(next);
    }
    digitString[index] = '\0';

    n = atoi(digitString);
}

//Uses iostream:
void newLine( )
 {
    using namespace std;

	//The rest of the definition of newLine is given in Display 6.7.

