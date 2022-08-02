//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace QuickNotes
{
    public ref class MainPage sealed
    {
    public:
        MainPage();

    private:
        void OnLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnAppSuspending(Platform::Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ args);
    };
}
