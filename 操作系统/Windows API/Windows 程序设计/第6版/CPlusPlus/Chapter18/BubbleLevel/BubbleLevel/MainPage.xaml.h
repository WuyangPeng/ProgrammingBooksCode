//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace BubbleLevel
{
    public ref class MainPage sealed
    {
    private:
        Windows::Devices::Sensors::Accelerometer^ accelerometer;

    public:
        MainPage();

    private:
        void OnMainPageLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnMainPageSizeChanged(Platform::Object^ sender, Windows::UI::Xaml::SizeChangedEventArgs^ args);
        void OnAccelerometerReadingChanged(Windows::Devices::Sensors::Accelerometer^ sender,
                                           Windows::Devices::Sensors::AccelerometerReadingChangedEventArgs^ args);
        void SetBubble(Windows::Devices::Sensors::AccelerometerReading^ accelerometerReading);
    };
}
