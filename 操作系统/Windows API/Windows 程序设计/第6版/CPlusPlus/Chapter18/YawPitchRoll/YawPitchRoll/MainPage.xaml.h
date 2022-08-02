//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace YawPitchRoll
{
    public ref class MainPage sealed
    {
    private:
        Windows::Devices::Sensors::Inclinometer^ inclinometer;

    public:
        MainPage();

    private:
        void OnMainPageLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnInclinometerReadingChanged(Windows::Devices::Sensors::Inclinometer^ sender,
                                          Windows::Devices::Sensors::InclinometerReadingChangedEventArgs^ args);
        void ShowYawPitchRoll(Windows::Devices::Sensors::InclinometerReading^ inclinometerReading);
        Platform::String^ Format(double number, int decimals);
    };
}
