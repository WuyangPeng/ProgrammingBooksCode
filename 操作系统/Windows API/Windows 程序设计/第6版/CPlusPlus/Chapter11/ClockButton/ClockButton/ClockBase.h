#pragma once

namespace ClockButton
{
    public ref class ClockBase : Windows::UI::Xaml::DependencyObject, 
                                 Windows::UI::Xaml::Data::INotifyPropertyChanged 
    {
    private:
        bool isEnabled;
        int hour, minute, second;
        int hourAngle, minuteAngle, secondAngle;
        Windows::Foundation::EventRegistrationToken renderingEventToken;

    internal: 
        ClockBase();

    public:
        virtual event Windows::UI::Xaml::Data::PropertyChangedEventHandler^ PropertyChanged;

        property bool IsEnabled
        {
            void set(bool value);
            bool get() { return isEnabled; };
        }

        property int Hour
        {
            void set(int value);
            int get() { return hour; }
        }

        property int Minute
        {
            void set(int value);
            int get() { return minute; }
        }

        property int Second
        {
            void set(int value);
            int get() { return second; }
        }

        property int HourAngle
        {
            void set(int value);
            int get() { return hourAngle; }
        }

        property int MinuteAngle
        {
            void set(int value);
            int get() { return minuteAngle; }
        }

        property int SecondAngle
        {
            void set(int value);
            int get() { return secondAngle; }
        }

    private:
        void OnCompositionTargetRendering(Platform::Object^ sender, Platform::Object^ args);

    protected:
        virtual void OnPropertyChanged(Platform::String^ propertyName);
    };
}
