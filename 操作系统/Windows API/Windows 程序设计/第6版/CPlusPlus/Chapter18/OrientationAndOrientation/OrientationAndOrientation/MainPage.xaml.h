//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace OrientationAndOrientation
{
    public ref class MainPage sealed
    {
    private:
        Windows::Devices::Sensors::SimpleOrientationSensor^ simpleOrientationSensor;

    public:
        MainPage();

    private:
        void OnSimpleOrientationChanged(Windows::Devices::Sensors::SimpleOrientationSensor^ sender, 
                                        Windows::Devices::Sensors::SimpleOrientationSensorOrientationChangedEventArgs^ args);
        void SetOrientationSensorText(Windows::Devices::Sensors::SimpleOrientation simpleOrientation);

        void OnDisplayPropertiesOrientationChanged(Platform::Object^ sender);
        void SetDisplayOrientationText(Windows::Graphics::Display::DisplayOrientations displayOrientation);
    };
}
