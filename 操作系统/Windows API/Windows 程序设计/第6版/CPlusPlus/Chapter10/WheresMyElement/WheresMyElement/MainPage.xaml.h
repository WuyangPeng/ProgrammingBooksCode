//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace WheresMyElement
{
    public ref class MainPage sealed
    {
    private:
        bool storyboardPaused;

    public:
        MainPage();

    protected:
        virtual void OnTapped(Windows::UI::Xaml::Input::TappedRoutedEventArgs^ args) override;
    };
}
