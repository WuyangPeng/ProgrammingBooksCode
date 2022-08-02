//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace SingleFingerRotate
{
    public ref class MainPage sealed
    {
    public:
        MainPage();

    protected:
        virtual void OnManipulationStarting(Windows::UI::Xaml::Input::ManipulationStartingRoutedEventArgs^ args) override;
        virtual void OnManipulationDelta(Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs^ args) override;
    };
}
