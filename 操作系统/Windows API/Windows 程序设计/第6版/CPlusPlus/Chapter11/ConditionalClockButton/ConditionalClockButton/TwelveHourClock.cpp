#include "pch.h"
#include "TwelveHourClock.h"

using namespace ConditionalClockButton;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Globalization;
using namespace Windows::Globalization::DateTimeFormatting;
using namespace Windows::UI;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;

TwelveHourClock::TwelveHourClock()
{
    // Initialize for Hour value of 0
    int hour12 = 12;
    bool isAm = true;
    bool isPm = false;
}

void TwelveHourClock::Hour12::set(int value)
{
    if (hour12 != value)
    {
        hour12 = value;
        OnPropertyChanged("Hour12");
    }
}

void TwelveHourClock::IsAm::set(bool value)
{
    if (isAm != value)
    {
        isAm = value;
        OnPropertyChanged("IsAm");
    }
}

void TwelveHourClock::IsPm::set(bool value)
{
    if (isPm != value)
    {
        isPm = value;
        OnPropertyChanged("IsPm");
    }
}

void TwelveHourClock::OnPropertyChanged(String^ propertyName)
{
    if (propertyName == "Hour")
    {
        this->Hour12 = (this->Hour - 1) % 12 + 1;
        this->IsAm = this->Hour < 12;
        this->IsPm = !this->IsAm;
    }

    ClockBase::OnPropertyChanged(propertyName);
}
