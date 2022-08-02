//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace SuspendResumeLog
{
    public ref class MainPage sealed
    {
    private:
        Windows::Storage::StorageFile^ logfile;

    public:
        MainPage();

    private:
        void OnLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnAppSuspending(Platform::Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ args);
        void OnAppResuming(Platform::Object^ sender, Platform::Object^ args);
        Platform::String^ GetFormattedDateTime();
    };
}
