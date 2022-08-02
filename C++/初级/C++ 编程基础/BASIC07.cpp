#include <iostream>
#include <string>
using namespace std;

int main()
{
    string name;
    short age;
 
    cout << "What is your first name? ";
    cin >> name;
 
    cout << "Thank you, " << name << endl;
 
    cout << "What is your age? ";
    cin >> age;
 
    if (age < 53)
        cout << "My, what a youngster!" << endl;
    else
        cout << "That is very old, " << name << ". " << endl;

    return 0;
}