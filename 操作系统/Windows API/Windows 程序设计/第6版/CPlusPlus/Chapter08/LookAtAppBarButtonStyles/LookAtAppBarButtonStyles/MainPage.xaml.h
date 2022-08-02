//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace LookAtAppBarButtonStyles
{
    public ref class MainPage sealed
    {
    private:
        ref struct Item
        {
        internal:
            Platform::String^ Key;
            wchar_t Symbol;
            Platform::String^ Text;
        };

        Windows::Foundation::Collections::IVector<Item^>^ appBarStyles;

    public:
        MainPage();

    private:
        void OnLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnRadioButtonChecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void DisplayList();
    };
}
