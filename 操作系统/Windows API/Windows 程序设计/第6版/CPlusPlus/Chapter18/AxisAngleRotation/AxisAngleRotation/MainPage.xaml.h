//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace AxisAngleRotation
{
    public ref class MainPage sealed
    {
    private:
        Windows::Devices::Sensors::Inclinometer^ inclinometer;
        Windows::Devices::Sensors::OrientationSensor^ orientationSensor;

    public:
        MainPage();

    private:
        void OnMainPageLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnInclinometerReadingChanged(Windows::Devices::Sensors::Inclinometer^ sender,
                                          Windows::Devices::Sensors::InclinometerReadingChangedEventArgs^ args);
        void ShowYawPitchRoll(Windows::Devices::Sensors::InclinometerReading^ inclinometerReading);
        void OnOrientationSensorChanged(Windows::Devices::Sensors::OrientationSensor^ sender,
                                        Windows::Devices::Sensors::OrientationSensorReadingChangedEventArgs^ args);
        void ShowOrientation(Windows::Devices::Sensors::OrientationSensorReading^ orientationReading);
        Platform::String^ Format(double number, int decimals);
    };
}
