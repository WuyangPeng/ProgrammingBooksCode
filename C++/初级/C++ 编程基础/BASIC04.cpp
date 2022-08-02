#include <iostream>
using namespace std;

int main()
{
    short Secret;
    short Guess;

    Secret = 3;

    cout << "Try to guess my number. Hint: It's from 0 to 9" << endl;
    cin >> Guess;

    while (Guess != Secret)
        {
        cout << "Sorry, that's not correct." << endl;
        cin >> Guess;
        }

    cout << "You guessed right!" << endl;

    return 0;
}
