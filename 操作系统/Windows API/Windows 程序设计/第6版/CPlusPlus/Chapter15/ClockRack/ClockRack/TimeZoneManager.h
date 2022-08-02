#pragma once

#include <Windows.h>    // this is the only class accessing Windows APIs
#include "TimeZoneDisplayInfo.h"

namespace ClockRack
{
    public ref class TimeZoneManager sealed
    {
    private:
        static bool areDisplayStringsInitialized;
        static Platform::Collections::Map<Platform::String^, Platform::String^>^ displayStrings;

        std::map<Platform::String^, DYNAMIC_TIME_ZONE_INFORMATION*> dynamicTzis;
        Platform::Collections::Vector<TimeZoneDisplayInfo^>^ displayInformation;
        Windows::Globalization::Calendar^ calendar;

    public:
        TimeZoneManager();

        property Windows::Foundation::Collections::IVector<TimeZoneDisplayInfo^>^ DisplayInformation
        {
            Windows::Foundation::Collections::IVector<TimeZoneDisplayInfo^>^ get() { return displayInformation; }
        }

        Windows::Foundation::DateTime GetLocalTime(Platform::String^ timeZoneKey);
    };
}
