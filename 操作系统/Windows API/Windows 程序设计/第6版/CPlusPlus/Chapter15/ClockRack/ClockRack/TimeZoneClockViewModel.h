#pragma once

namespace ClockRack
{
    [Windows::UI::Xaml::Data::BindableAttribute]
    public ref class TimeZoneClockViewModel sealed : Windows::UI::Xaml::Data::INotifyPropertyChanged 
    {
    private:
        // Backing stores for dependency properties
        Platform::String^ location;
        Platform::String^ timeZoneKey;
        Windows::UI::Color background;
        Windows::UI::Color foreground;
        Platform::String^ backgroundName;
        Platform::String^ foregroundName;
        Windows::Foundation::DateTime dateTime;
        Platform::String^ formattedDateTime;
        double hourAngle, minuteAngle, secondAngle;

        // Helpers
        ReflectionHelper::TypeInformation^ colorsTypeInfo;
        Windows::Globalization::Calendar^ calendar;
        Windows::Globalization::DateTimeFormatting::DateTimeFormatter^ dateFormatter;
        Windows::Globalization::DateTimeFormatting::DateTimeFormatter^ timeFormatter;

    public:
        TimeZoneClockViewModel();
        virtual event Windows::UI::Xaml::Data::PropertyChangedEventHandler^ PropertyChanged;

        property Platform::String^ Location
        {
            Platform::String^ get();
            void set(Platform::String^ value);
        }

        property Platform::String^ TimeZoneKey
        {
            Platform::String^ get();
            void set(Platform::String^ value);
        }

        property Platform::String^ BackgroundName
        {
            Platform::String^ get();
            void set(Platform::String^ value);
        }

        property Windows::UI::Color Background
        {
            Windows::UI::Color get();
            void set(Windows::UI::Color value);
        }

        property Platform::String^ ForegroundName
        {
            Platform::String^ get();
            void set(Platform::String^ value);
        }

        property Windows::UI::Color Foreground
        {
            Windows::UI::Color get();
            void set(Windows::UI::Color value);
        }

        property Windows::Foundation::DateTime DateTime
        {
            Windows::Foundation::DateTime get();
            void set(Windows::Foundation::DateTime value);
        }

        property Platform::String^ FormattedDateTime
        {
            Platform::String^ get();
        }

        property double HourAngle
        {
            double get();
            void set(double value);
        }

        property double MinuteAngle
        {
            double get();
            void set(double value);
        }

        property double SecondAngle
        {
            double get();
            void set(double value);
        }

    private:
        Windows::UI::Color NameToColor(Platform::String^ name);
        Platform::String^ ColorToName(Windows::UI::Color color);
        bool AreColorsEqual(Windows::UI::Color color1, Windows::UI::Color color2);

    protected:
        void OnPropertyChanged(Platform::String^ propertyName);
    };
}
