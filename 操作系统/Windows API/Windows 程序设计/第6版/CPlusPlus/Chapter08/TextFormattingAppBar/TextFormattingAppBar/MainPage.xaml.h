//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace TextFormattingAppBar
{
    public ref class MainPage sealed
    {
    public:
        MainPage();

    private:
        void OnBoldAppBarCheckBoxChecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnItalicAppBarCheckBoxChecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnUnderlineAppBarCheckBoxChecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnFontColorAppBarRadioButtonChecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
    };
}
