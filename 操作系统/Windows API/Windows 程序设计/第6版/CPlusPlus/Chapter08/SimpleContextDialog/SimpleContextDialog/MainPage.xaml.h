//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace SimpleContextDialog
{
    public ref class MainPage sealed
    {
    public:
        MainPage();

    private:
        void OnTextBlockRightTapped(Platform::Object^ sender, Windows::UI::Xaml::Input::RightTappedRoutedEventArgs^ args);
        bool AreColorsEqual(Windows::UI::Color clr1, Windows::UI::Color clr2);
        void OnButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnRadioButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
    };
}
