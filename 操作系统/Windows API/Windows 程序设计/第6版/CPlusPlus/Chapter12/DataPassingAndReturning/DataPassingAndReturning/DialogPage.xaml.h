//
// DialogPage.xaml.h
// Declaration of the DialogPage class
//

#pragma once

#include "DialogPage.g.h"
#include "PassData.h"
#include "ReturnData.h"

namespace DataPassingAndReturning
{
    public ref class DialogPage sealed
    {
    public:
        DialogPage();

         event Windows::Foundation::EventHandler<ReturnData^>^ Completed;

    protected:
        virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
        virtual void OnNavigatedFrom(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
        
    private:
        void OnReturnButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
    };
}
