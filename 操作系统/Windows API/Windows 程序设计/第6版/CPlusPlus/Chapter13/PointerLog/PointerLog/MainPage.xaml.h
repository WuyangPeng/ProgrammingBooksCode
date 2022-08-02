//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include "LoggerControl.xaml.h"

namespace PointerLog
{
    public ref class MainPage sealed
    {
    private:
        Windows::UI::Xaml::DispatcherTimer^ timer;

    public:
        MainPage();

    protected:
        void OnClearButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnCaptureToggleButtonChecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnReleaseCapturesButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnTimerTick(Platform::Object^ sender, Platform::Object^ args);
    };
}
