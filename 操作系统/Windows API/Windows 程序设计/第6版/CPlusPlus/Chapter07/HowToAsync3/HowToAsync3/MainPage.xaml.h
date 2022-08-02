//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace HowToAsync3
{
    public ref class MainPage sealed
    {
    public:
        MainPage();

    private:
        void OnButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
    };
}
