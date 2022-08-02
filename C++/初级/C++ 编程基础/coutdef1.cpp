#include <iostream>
#include <sstream>
#include <string>
using namespace std;

int main()
{
    stringstream FormatStream1;
    stringstream FormatStream2;
    string date1;
    string date2;

    short year1 = 1996;
    short month1 = 12;
    short day1 = 28;

    short year2 = 1996;
    short month2 = 7;
    short day2 = 28;

    FormatStream1 << year1 << month1 << day1;
    FormatStream1 >> date1;

    FormatStream2 << year2 << month2 << day2;
    FormatStream2 >> date2;

    cout << "date1: " << date1 << ", date2: " << date2 << endl;

    if (date1 < date2)
      cout << "date1 is less than date2" << endl;
    else if (date1 == date2)
      cout << "date1 is the same as date2" << endl;
    else
      cout << "date1 is greater than date2" << endl;

    return 0;
}
