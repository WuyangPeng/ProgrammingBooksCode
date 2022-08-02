//DISPLAY 10.4 Class with Private Members
//Program to demonstrate the class DayOfYear.
#include <iostream>
using namespace std;

class DayOfYear
{
public:
    void input( );
    void output( );

    void set(int newMonth, int newDay);
    //Precondition: newMonth and newDay form a possible date.
    //Postcondition: The date is reset according to the arguments.

    int getMonth( );
    //Returns the month, 1 for January, 2 for February, etc.

    int getDay( );
    //Returns the day of the month.
private:
    void checkDate( );
    int month;
    int day;
};

int main( )
{
    DayOfYear today, bachBirthday;
    cout << "Enter today's date:\n";
    today.input( );
    cout << "Today's date is ";
    today.output( );

    bachBirthday.set(3, 21);
    cout << "J. S. Bach's birthday is ";
    bachBirthday.output( );

    if ( today.getMonth( ) = = bachBirthday.getMonth( ) &&
               today.getDay( ) = = bachBirthday.getDay( ) )
        cout << "Happy Birthday Johann Sebastian!\n";
    else
        cout << "Happy Unbirthday Johann Sebastian!\n";
    return 0;
}
//Uses iostream:
void DayOfYear::input( )
{
    cout << "Enter the month as a number: ";


cin >> month;
    cout << "Enter the day of the month: ";
    cin >> day;
    checkDate( );
}

void DayOfYear::output( )
    //The rest of the definition of DayOfYear::output is given in Display 10.3.>

void DayOfYear::set(int newMonth, int newDay)
{
    month = newMonth;
    day = newDay;
    checkDate();
}

void DayOfYear::checkDate( )
{
    if ((month < 1) || (month > 12) || (day < 1) || (day > 31))
    {
        cout << "Illegal date. Aborting program.\n";
        exit(1);
    }
}

int DayOfYear::getMonth( )
{
    return month;
}

int DayOfYear::getDay( )
{
    return day;
}

