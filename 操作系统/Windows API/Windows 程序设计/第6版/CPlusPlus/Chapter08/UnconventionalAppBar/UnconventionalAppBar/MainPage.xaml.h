//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace UnconventionalAppBar
{
    public ref class MainPage sealed
    {
    public:
        MainPage();

    private:
        void OnAppBarButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
    };
}
