//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace HowToAsync1
{
    public ref class MainPage sealed
    {
    private:
        Windows::UI::Color clr;

    public:
        MainPage();

    private:
        void OnButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnMessageDialogShowAsyncCompleted(Windows::Foundation::IAsyncOperation<Windows::UI::Popups::IUICommand^>^ asyncInfo,
                                               Windows::Foundation::AsyncStatus asyncStatus);
        void OnDispatcherRunAsyncCallback();
    };
}
