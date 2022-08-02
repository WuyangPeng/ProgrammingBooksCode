//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace ThreeDeeSpinningText
{
    public ref class MainPage sealed
    {
    public:
        MainPage();

    private:
        void OnBeginStopButton(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnPauseResumeButton(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        Windows::UI::Xaml::FrameworkElement^ GetSibling(Windows::UI::Xaml::FrameworkElement^ element, int relativeIndex);
    };
}
