//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace AccelerometerAndSimpleOrientation
{
    public ref class MainPage sealed
    {
    private:
        Windows::Devices::Sensors::Accelerometer^ accelerometer;
        Windows::Devices::Sensors::SimpleOrientationSensor^ simpleOrientationSensor;
        Windows::Foundation::EventRegistrationToken accelerometerEventToken;
        Windows::Foundation::EventRegistrationToken orientationEventToken;

    public:
        MainPage();

    protected:
        virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
        virtual void OnNavigatedFrom(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;

    private:
        void OnMainPageLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnAccelerometerReadingChanged(Windows::Devices::Sensors::Accelerometer^ sender,
                                           Windows::Devices::Sensors::AccelerometerReadingChangedEventArgs^ args);
        void SetAccelerometerText(Windows::Devices::Sensors::AccelerometerReading^ accelerometerReading);
        Platform::String^ Format(double number, int decimals);
        void OnSimpleOrientationChanged(Windows::Devices::Sensors::SimpleOrientationSensor^ sender, 
                                        Windows::Devices::Sensors::SimpleOrientationSensorOrientationChangedEventArgs^ args);
        void SetOrientationSensorText(Windows::Devices::Sensors::SimpleOrientation simpleOrientation);
    };
}
