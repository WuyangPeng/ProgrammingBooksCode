//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include "DialogPage.xaml.h"
#include "PassData.h"
#include "ReturnData.h"

namespace DataPassingAndReturning
{
    public ref class MainPage sealed
    {
    private:
        Windows::Foundation::EventRegistrationToken completedEventToken;

    public:
        MainPage();

    protected:
        virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
        virtual void OnNavigatedFrom(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;

    private:
        void OnGotoButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnDialogPageCompleted(Platform::Object^ sender, ReturnData^ args);
    };
}
