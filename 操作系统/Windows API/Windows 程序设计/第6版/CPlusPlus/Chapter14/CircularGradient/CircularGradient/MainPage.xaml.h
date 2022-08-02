//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace CircularGradient
{
    public ref class MainPage sealed
    {
    public:
        MainPage();

    protected:
        void OnMainPageLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs ^ args);
    };
}
