#include <iostream>
using namespace std;

int main()
{
    short x;

    cout << "Elena can increase her $10 allowance each week ";
    cout << "by adding new chores." << endl;

    cout << "For every extra chore Elena does, she gets ";
    cout << "another dollar." << endl;

    cout << "How many extra chores were done? " << endl; 
    cin >> x;

    if (x==0)
        {
        cout << "There is no extra allowance for Elena ";
        cout << "this week. " << endl; 
        }
    else
        {
        cout << "Elena will now earn " << 10 + x;
        cout << " dollars this week." << endl; 
        }

    return 0;
}
