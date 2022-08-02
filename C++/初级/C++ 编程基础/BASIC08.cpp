#include <iostream>
#include <string>
using namespace std;

int main()
{
    string answer;

    cout << "Please respond to the following statement ";
    cout << "with either true or false\n";

    cout << "Susan is the world's most tenacious novice.\n";
    cin >> answer;

    if (answer != "true")
        if (answer != "false")
            cout << "Please answer with either true or false.";

    if (answer == "true")
        cout << "Your answer is correct\n";

    if (answer == "false")
        cout << "Your answer is erroneous\n";

    return 0;
}