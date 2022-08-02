//
// TimeZoneClock.xaml.h
// Declaration of the TimeZoneClock class
//

#pragma once

#include "TimeZoneClock.g.h"
#include "TimeZoneClockViewModel.h"

namespace ClockRack
{
    public ref class TimeZoneClock sealed
    {
    public:
        TimeZoneClock();

        static property double AspectRatio
        {
            double get() { return 1 / 1.5; }
        }
    };
}
