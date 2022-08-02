//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace CustomButtonTemplate
{
    public ref class MainPage sealed
    {
    public:
        MainPage();

    private:
        void OnButton1Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnButton3Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
    };
}
