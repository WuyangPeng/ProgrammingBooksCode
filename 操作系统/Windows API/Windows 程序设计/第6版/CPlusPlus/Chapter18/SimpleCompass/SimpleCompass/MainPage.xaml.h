//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace SimpleCompass
{
    public ref class MainPage sealed
    {
    private:
        Windows::Devices::Sensors::Compass^ compass;

    public:
        MainPage();

    private:
        void OnMainPageLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnCompassReadingChanged(Windows::Devices::Sensors::Compass^ sender,
                                     Windows::Devices::Sensors::CompassReadingChangedEventArgs^ args);
        void ShowCompassValues(Windows::Devices::Sensors::CompassReading^ compassReading);
    };
}
