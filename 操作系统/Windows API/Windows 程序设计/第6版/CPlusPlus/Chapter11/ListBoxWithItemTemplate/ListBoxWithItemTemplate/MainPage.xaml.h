//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace ListBoxWithItemTemplate
{
    public ref class MainPage sealed
    {
    public:
        MainPage();

    private:
        void OnItemLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
    };
}
