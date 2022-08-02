//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace DigitalClock
{
    public ref class MainPage sealed
    {
    private:
        Windows::Globalization::Calendar^ calendar;
        Windows::Globalization::DateTimeFormatting::DateTimeFormatter^ formatter;

    public:
        MainPage();

    private:
        void OnTimerTick(Platform::Object^ sender, Platform::Object^ args);
    };
}
