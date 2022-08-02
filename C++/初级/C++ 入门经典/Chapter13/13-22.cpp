//DISPLAY 13.22 Program Using the Queue Class
//Program to demonstrate use of the Queue class.
#include <iostream>
#include "queue.h"
using namespace std;
using namespace queuesavitch;

int main( )
{
    Queue q;
    char next, ans;

    do
    {
        cout << "Enter a word: ";
        cin.get(next);
        while (next != '\n')
        {
            q.add(next);
            cin.get(next);
        }

cout << "You entered:: ";
        while ( ! q.empty( ) )
            cout << q.remove( );
        cout << endl;

        cout << "Again?(y/n): ";
        cin >> ans;
        cin.ignore(10000, '\n');
    }while (ans !='n' && ans != 'N');

    return 0;
}
