//DISPLAY 8.5 Program Using the Class string
//Demonstrates getline and cin.get
#include <iostream>
#include <string>

void newLine( );

int main( )
{
    using namespace std;

    string firstName, lastName, recordName;
    string motto = "Your records are our records.";

    cout << "Enter your first and last name:\n";
    cin >> firstName >> lastName;
    newLine( );

    recordName = lastName + ", " + firstName;
    cout << "Your name in our records is: ";
    cout << recordName << endl;

    cout << "Our motto is\n"
         << motto << endl;
    cout << "Please suggest a better (one-line) motto:\n";
    getline(cin, motto);
    cout << "Our new motto will be:\n";
    cout << motto << endl;

    return 0;
}

//Uses iostream:
void newLine( )
{
    using namespace std;

    char nextChar;
    do
    {
        cin.get(nextChar);
    } while (nextChar != '\n');
}


