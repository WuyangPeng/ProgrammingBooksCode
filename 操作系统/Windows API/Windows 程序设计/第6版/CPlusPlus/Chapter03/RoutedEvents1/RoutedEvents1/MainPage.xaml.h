//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace RoutedEvents1
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public ref class MainPage sealed
    {
    public:
        MainPage();

    private:
        void OnGridTapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ args);
    };
}
