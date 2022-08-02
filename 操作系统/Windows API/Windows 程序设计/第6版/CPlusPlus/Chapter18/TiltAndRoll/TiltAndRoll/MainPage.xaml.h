//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace TiltAndRoll
{
    public ref class MainPage sealed
    {
    private:
        static const int GRAVITY = 5000;     // pixels per second squared
        static const int BALL_RADIUS = 32;
        Windows::Devices::Sensors::Accelerometer^ accelerometer;
        Windows::Foundation::TimeSpan timeSpan;
        D2D1_VECTOR_2F acceleration;
        D2D1_VECTOR_2F ballVelocity;
        D2D1_VECTOR_2F ballPosition;
        
    public:
        MainPage();

    private:
        void OnMainPageLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnCompositionTargetRendering(Platform::Object^ sender, Platform::Object^ args);
    };
}
