//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include "LineJoinRadioButton.h"
#include "LineCapRadioButton.h"

namespace LineCapsAndJoinsWithCustomClass
{
    public ref class MainPage sealed
    {
    public:
        MainPage();

    private:
        void OnStartLineCapRadioButtonChecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnEndLineCapRadioButtonChecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnLineJoinRadioButtonChecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
    };
}
