//DISPLAY 11.2 Equality Function as a Friend
//Demonstrates the function equal.
//In this version equal is a friend of the class DayOfYear.
#include <iostream>
using namespace std;

class DayOfYear
{
public:
    friend bool equal(DayOfYear date1, DayOfYear date2);
    //Precondition: date1 and date2 have values.
    //Returns true if date1 and date2 represent the same date;
    //otherwise, returns false.

    DayOfYear(int theMonth, int theDay);
    //Precondition: theMonth and theDay form a
    //possible date. Initializes the date according
    //to the arguments.

    DayOfYear( );
    //Initializes the date to January first.

    void input( );

    void output( );

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
//The main part of the program is the same as in Display 11.1.
}

bool equal(DayOfYear date1, DayOfYear date2)
{
    return ( date1.month == date2.month &&
                           date1.day == date2.day );
}

//The rest of this display, including the Sample Dialogue, is the same as in Display 11.1.

