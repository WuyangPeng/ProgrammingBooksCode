//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace SimpleKeypad
{
    public ref class MainPage sealed
    {
    private:
        std::wstring inputString;

    public:
        MainPage();

    private:
        void OnCharButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnDeleteButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void FormatText();
    };
}
