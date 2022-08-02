//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace PrimitivePad
{
    public ref class MainPage sealed
    {
    public:
        MainPage();

        void OnFileOpenButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnFileSaveAsButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnWrapButtonChecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
    };
}
