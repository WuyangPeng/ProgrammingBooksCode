//DISPLAY 12.6 Placing a Class in a Namespace Header File
//Header file dtime.h: This is the interface for the class DigitalTime.
//Values of this type are times of day. The values are input and output in
//24-hour notation, as in 9:30 for 9:30 AM and 14:45 for 2:45 PM.

#ifndef DTIME_H
#define DTIME_H

#include <iostream>
using namespace std;

namespace dtimesavitch
{

    class DigitalTime
    {

        //The definition of the class DigitalTime is the same as in Display 12.1.
    };
}//end dtimesavitch

#endif //DTIME_H
