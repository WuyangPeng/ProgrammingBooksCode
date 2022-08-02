//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace RoutedEvents6
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public ref class MainPage sealed
    {
    public:
        MainPage();

    private:
        void OnTextBlockTapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ args);
        void OnPageTapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ args);
        Windows::UI::Xaml::Media::Brush^ GetRandomBrush();
    };
}
