//DISPLAY 12.7 Placing a Class in a NamespaceImplementation File
//Implementation file dtime.cpp (your system may require some
//suffix other than .cpp): This is the IMPLEMENTATION of the ADT DigitalTime.
//The interface for the class DigitalTime is in the header file dtime.h.
#include <iostream>
#include <cctype>
#include <cstdlib>
#include "dtime.h"
using namespace std;

namespace
{
    //These function declarations are for use in the definition of
    //the overloaded input operator >>:

    void readHour(istream& ins, int& theHour);
    //Precondition: Next input in the stream ins is a time in 24-hour notation,
    //like 9:45 or 14:45.
    //Postcondition: theHour has been set to the hour part of the time.
    //The colon has been discarded and the next input to be read is the minute.

    void readMinute(istream& ins, int& theMinute);
    //Reads the minute from the stream ins after readHour has read the hour.

    int digitToInt(char c);
    //Precondition: c is one of the digits '0' through '9'.
    //Returns the integer for the digit; for example, digitToInt('3')
    //returns 3.
}//unnamed namespace


namespace dtimesavitch
{
    bool operator ==(const DigitalTime& time1, const DigitalTime& time2)
       //The rest of the definition of = = is the same as in Display 12.2.

    DigitalTime::DigitalTime( )
       //The rest of the definition of this constructor is the same as in Display 12.2.

    DigitalTime::DigitalTime(int theHour, int theMinute)
       //The rest of the definition of this constructor is the same as in Display 12.2.
    
    void DigitalTime::advance(int minutesAdded)
       //The rest of the definition of this advance function is the same as in Display 12.2.

    void DigitalTime::advance(int hoursAdded, int minutesAdded)
        //The rest of the definition of this advance function is the same as in Display 12.2.

    ostream& operator <<(ostream& outs, const DigitalTime& theObject)
       //The rest of the definition of << is the same as in Display 12.2.

    //Uses iostream and functions in the unnamed namespace:
    istream& operator >>(istream& ins, DigitalTime& theObject)
    {
        readHour(ins, theObject.hour);
        readMinute(ins, theObject.minute);
        return ins;
    }
} //dtimesavitch


namespace
{
    int digitToInt(char c)
        //The rest of the definition of digitToInt is the same as in Display 12.2.>

    void readMinute(istream& ins, int& theMinute)
       //The rest of the definition of readMinute is the same as in Display 12.2.>

    void readHour(istream& ins, int& theHour)
       //The rest of the definition of readHour is the same as in Display 12.2.

}//unnamed namespace
