//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace HarderCameraCapture
{
    public ref class MainPage sealed
    {
    private:
        Platform::Agile<Windows::Media::Capture::MediaCapture^> mediaCapture;
        bool ignoreTaps;
        Windows::Foundation::EventRegistrationToken timerTickEventToken;

    public:
        MainPage();

    private:
        void OnMainPageLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);

    protected:
        virtual void OnTapped(Windows::UI::Xaml::Input::TappedRoutedEventArgs^ args) override;

    private:
        void OnTimerTick(Platform::Object^ sender, Platform::Object^ args);
    };
}
