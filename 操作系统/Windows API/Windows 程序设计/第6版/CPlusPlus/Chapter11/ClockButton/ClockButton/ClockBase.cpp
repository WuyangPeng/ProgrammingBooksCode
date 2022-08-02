#include "pch.h"
#include "ClockBase.h"

using namespace ClockButton;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Globalization;
using namespace Windows::Globalization::DateTimeFormatting;
using namespace Windows::UI;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;

ClockBase::ClockBase()
{
    isEnabled = false;
}

void ClockBase::IsEnabled::set(bool value)
{
    if (isEnabled != value)
    {
        isEnabled = value;

        if (isEnabled)
            renderingEventToken = CompositionTarget::Rendering += 
                        ref new EventHandler<Object^>(this, &ClockBase::OnCompositionTargetRendering);
        else
            CompositionTarget::Rendering -= renderingEventToken;

        OnPropertyChanged("IsEnabled");
    }
}

void ClockBase::Hour::set(int value)
{
    if (hour != value)
    {
        hour = value;
        OnPropertyChanged("Hour");
    }
}

void ClockBase::Minute::set(int value)
{
    if (minute != value)
    {
        minute = value;
        OnPropertyChanged("Minute");
    }
}

void ClockBase::Second::set(int value)
{
    if (second != value)
    {
        second = value;
        OnPropertyChanged("Second");
    }
}

void ClockBase::HourAngle::set(int value)
{
    if (hourAngle != value)
    {
        hourAngle = value;
        OnPropertyChanged("HourAngle");
    }
}

void ClockBase::MinuteAngle::set(int value)
{
    if (minuteAngle != value)
    {
        minuteAngle = value;
        OnPropertyChanged("MinuteAngle");
    }
}

void ClockBase::SecondAngle::set(int value)
{
    if (secondAngle != value)
    {
        secondAngle = value;
        OnPropertyChanged("SecondAngle");
    }
}

void ClockBase::OnCompositionTargetRendering(Object^ sender, Object^ args)
{
    SYSTEMTIME dt;
    GetLocalTime(&dt);
    this->Hour = dt.wHour;
    this->Minute = dt.wMinute;
    this->Second = dt.wSecond;
    this->HourAngle = 30 * dt.wHour + dt.wMinute / 2;
    this->MinuteAngle = 6 * dt.wMinute + dt.wSecond / 10;
    this->SecondAngle = 6 * dt.wSecond + dt.wMilliseconds / 166;
}

void ClockBase::OnPropertyChanged(String^ propertyName)
{
    PropertyChanged(this, ref new PropertyChangedEventArgs(propertyName));
}
