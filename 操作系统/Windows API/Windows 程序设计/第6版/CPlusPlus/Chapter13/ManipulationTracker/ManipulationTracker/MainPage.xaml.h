//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include "ManipulationModeCheckBox.h"

namespace ManipulationTracker
{
    public ref class MainPage sealed
    {
    public:
        MainPage();

    protected:
        void OnManipulationModeCheckBoxChecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        virtual void OnManipulationDelta(Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs^ args) override;
    };
}
