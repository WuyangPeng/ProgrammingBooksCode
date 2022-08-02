//DISPLAY 2.5 The string class
#include <iostream>
#include <string>
using namespace std;
int main()
{
    string middleName, petName;
    string alterEgoName;

    cout << "Enter your middle name and the name of your pet.\n";
    cin >> middleName;
    cin >> petName;

    alterEgoName = petName + " " + middleName;

    cout << "The name of your alter ego is ";
    cout << alterEgoName << "." << endl;

    return 0;

}
