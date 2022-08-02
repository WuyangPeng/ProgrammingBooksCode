#pragma once

#include "..\\..\\ClockButton\\ClockButton\\ClockBase.h"

namespace ConditionalClockButton
{
    [Windows::UI::Xaml::Data::BindableAttribute]
    public ref class TwelveHourClock sealed : ClockButton::ClockBase
    {
    private:
        int hour12;
        bool isAm, isPm;

    public:
        TwelveHourClock();

        property int Hour12
        {
            void set(int value);
            int get() { return hour12; };
        }

        property bool IsAm
        {
            void set(bool value);
            bool get() { return isAm; }
        }

        property bool IsPm
        {
            void set(bool value);
            bool get() { return isPm; }
        }

    protected:
        virtual void OnPropertyChanged(Platform::String^ propertyName) override;
    };
}
