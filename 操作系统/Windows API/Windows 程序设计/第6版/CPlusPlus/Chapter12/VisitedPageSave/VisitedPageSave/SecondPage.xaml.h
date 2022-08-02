//
// SecondPage.xaml.h
// Declaration of the SecondPage class
//

#pragma once

#include "SaveStatePage.h"
#include "SecondPage.g.h"
#include "MainPage.xaml.h"

namespace VisitedPageSave
{
    public ref class SecondPage sealed
    {
    public:
        SecondPage();

    protected:
        virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
        virtual void OnNavigatedFrom(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;

    private:
        void OnGotoButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnForwardButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnBackButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
    };
}
