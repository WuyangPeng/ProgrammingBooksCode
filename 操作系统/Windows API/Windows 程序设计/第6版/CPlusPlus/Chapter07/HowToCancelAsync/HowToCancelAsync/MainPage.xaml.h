//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace HowToCancelAsync
{
    public ref class MainPage sealed
    {
    private:
        Concurrency::cancellation_token_source cancellationTokenSource;

    public:
        MainPage();

    private:
        void OnButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnTimerTick(Platform::Object^ sender, Platform::Object^ args);
    };
}
