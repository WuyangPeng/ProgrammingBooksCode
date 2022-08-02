#include <iostream>
using std::cout;
using std::endl;

int main()
{
    char High[10];
    char Middle[10];
    char Low[10];
    char* Alias;
    short i;
    
    for (i = 0; i < 10; i ++)
        {
        Middle[i] = 'A' + i;
        High[i] = '0';
        Low[i] ='1';
        }

    Alias = Middle;

    for (i = 10; i < 20; i ++)
        {
        Alias[i] = 'a' + i;
        }

    cout << "Low: ";
    for (i = 0; i < 10; i ++)
        cout << Low[i];

    cout << endl;

    cout << "Middle: ";
    for (i = 0; i < 10; i ++)
        cout << Middle[i];

    cout << endl;

    cout << "Alias: ";
    for (i = 0; i < 10; i ++)
        cout << Alias[i];

    cout << endl;

    cout << "High: ";
    for (i = 0; i < 10; i ++)
        cout << High[i];

    cout << endl;
}
