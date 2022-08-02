//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include "WrapOptionsDialog.xaml.h"

namespace AppBarPad
{
    public ref class MainPage sealed
    {
    public:
        MainPage();

    private:
        void OnFontIncreaseAppBarButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnFontDecreaseAppBarButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void ChangeFontSize(double multiplier);

        void OnWrapOptionAppBarButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);

        void OnOpenAppBarButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnSaveAsAppBarButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
    };
}
