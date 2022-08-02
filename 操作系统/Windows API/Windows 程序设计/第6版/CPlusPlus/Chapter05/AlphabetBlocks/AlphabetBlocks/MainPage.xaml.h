//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace AlphabetBlocks
{
    public ref class MainPage sealed
    {
    private:
        static const int BUTTON_SIZE = 60;
        static const int BUTTON_FONT = 18;
        Platform::String^ blockChars;
        static Windows::UI::Color colors[5];

    public:
        MainPage();

    private:
        void OnGridSizeChanged(Platform::Object^ sender, Windows::UI::Xaml::SizeChangedEventArgs^ args);
        Windows::UI::Xaml::Controls::Button^ MakeButton(int index);
        void OnButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
    };
}
