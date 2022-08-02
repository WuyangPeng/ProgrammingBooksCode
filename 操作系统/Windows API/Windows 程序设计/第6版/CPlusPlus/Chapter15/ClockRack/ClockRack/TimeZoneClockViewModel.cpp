#include "pch.h"
#include "TimeZoneClockViewModel.h"

using namespace ClockRack;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Globalization;
using namespace Windows::Globalization::DateTimeFormatting;
using namespace Windows::UI;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Interop;

// C# assembly
using namespace ReflectionHelper;

TimeZoneClockViewModel::TimeZoneClockViewModel()
{
    location = "New York City";
    timeZoneKey = "Eastern Standard Time";
    background = Colors::Yellow;
    foreground = Colors::Blue;
    backgroundName = "Yellow";
    foregroundName = "Blue";
    calendar = ref new Calendar();
    dateFormatter = ref new DateTimeFormatter(YearFormat::Full, MonthFormat::Full, DayFormat::Default, DayOfWeekFormat::Full);
    timeFormatter = ref new DateTimeFormatter(HourFormat::Default, MinuteFormat::Default, SecondFormat::None);
    TypeName colorsTypeName = { Colors::typeid->FullName, TypeKind::Metadata };
    colorsTypeInfo = ref new TypeInformation(colorsTypeName);
}

void TimeZoneClockViewModel::Location::set(String^ value)
{
    if (location != value)
    {
        location = value;
        OnPropertyChanged("Location");
    }
}

String^ TimeZoneClockViewModel::Location::get()
{
    return location;
}

void TimeZoneClockViewModel::TimeZoneKey::set(String^ value)
{
    if (timeZoneKey != value)
    {
        timeZoneKey = value;
        OnPropertyChanged("TimeZoneKey");
    }
}

String^ TimeZoneClockViewModel::TimeZoneKey::get()
{
    return timeZoneKey;
}

void TimeZoneClockViewModel::BackgroundName::set(String^ value)
{
    if (backgroundName != value)
    {
        backgroundName = value;
        OnPropertyChanged("BackgroundName");
        this->Background = NameToColor(value);
    }
}

String^ TimeZoneClockViewModel::BackgroundName::get()
{
    return backgroundName;
}

void TimeZoneClockViewModel::Background::set(Color value)
{
    if (!background.Equals(value))
    {
        background = value;
        OnPropertyChanged("Background");
        this->BackgroundName = ColorToName(value);
    }
}

Color TimeZoneClockViewModel::Background::get()
{
    return background;
}

void TimeZoneClockViewModel::ForegroundName::set(String^ value)
{
    if (foregroundName != value)
    {
        foregroundName = value;
        OnPropertyChanged("ForegroundName");
        this->Foreground = NameToColor(value);
    }
}

String^ TimeZoneClockViewModel::ForegroundName::get()
{
    return foregroundName;
}

void TimeZoneClockViewModel::Foreground::set(Color value)
{
    if (!foreground.Equals(value))
    {
        foreground = value;
        OnPropertyChanged("Foreground");
        this->ForegroundName = ColorToName(value);
    }
}

Color TimeZoneClockViewModel::Foreground::get()
{
    return foreground;
}

void TimeZoneClockViewModel::DateTime::set(Windows::Foundation::DateTime value)
{
    if (!dateTime.Equals(value))
    {
        dateTime = value;
        OnPropertyChanged("DateTime");
        OnPropertyChanged("FormattedDateTime");

        calendar->SetDateTime(value);
        this->SecondAngle = 6 * (calendar->Second + calendar->Nanosecond / 1000000000.0);
        this->MinuteAngle = 6 * calendar->Minute + this->SecondAngle / 60;
        this->HourAngle = 30 * (calendar->Hour % 12) + this->MinuteAngle / 12;
    }
}

DateTime TimeZoneClockViewModel::DateTime::get()
{
    return dateTime;
}

String^ TimeZoneClockViewModel::FormattedDateTime::get()
{
    return dateFormatter->Format(this->DateTime) + " " + timeFormatter->Format(this->DateTime);
}

void TimeZoneClockViewModel::HourAngle::set(double value)
{
    if (hourAngle != value)
    {
        hourAngle = value;
        OnPropertyChanged("HourAngle");
    }
}

double TimeZoneClockViewModel::HourAngle::get()
{
    return hourAngle;
}

void TimeZoneClockViewModel::MinuteAngle::set(double value)
{
    if (minuteAngle != value)
    {
        minuteAngle = value;
        OnPropertyChanged("MinuteAngle");
    }
}

double TimeZoneClockViewModel::MinuteAngle::get()
{
    return minuteAngle;
}

void TimeZoneClockViewModel::SecondAngle::set(double value)
{
    if (secondAngle != value)
    {
        secondAngle = value;
        OnPropertyChanged("SecondAngle");
    }
}

double TimeZoneClockViewModel::SecondAngle::get()
{
    return secondAngle;
}

Color TimeZoneClockViewModel::NameToColor(String^ name)
{
    return (Color)colorsTypeInfo->GetDeclaredProperty(name)->GetValue(nullptr);
}

String^ TimeZoneClockViewModel::ColorToName(Color color)
{
    for each (PropertyInformation^ property in colorsTypeInfo->DeclaredProperties)
        if (AreColorsEqual(color, (Color)property->GetValue(nullptr)))
            return property->Name;

    return "";
}

bool TimeZoneClockViewModel::AreColorsEqual(Color color1, Color color2)
{
    return color1.A == color2.A && 
           color1.R == color2.R && 
           color1.G == color2.G && 
           color1.B && color2.B;
}

void TimeZoneClockViewModel::OnPropertyChanged(String^ propertyName)
{
    PropertyChanged(this, ref new PropertyChangedEventArgs(propertyName));
}
