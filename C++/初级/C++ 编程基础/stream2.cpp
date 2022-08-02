#include <iostream>
#include <sstream>
using namespace std;

int main()
{
    stringstream FormatStream;
    string date;

    short year = 1996;
    short month = 7;
    short day = 28;

    FormatStream << year;
    FormatStream << month;
    FormatStream << day;

    FormatStream >> date;

    cout << "date: " << date << endl;

    return 0;
}
