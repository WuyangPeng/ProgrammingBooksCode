//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include "SecondPage.xaml.h"

namespace SimplePageNavigation
{
    public ref class MainPage sealed
    {
    public:
        MainPage();

    protected:
        virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;

    private:
        void OnGotoButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnForwardButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnBackButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
    };
}
