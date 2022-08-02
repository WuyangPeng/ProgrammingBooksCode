//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace CenteredTransforms
{
    public ref class MainPage sealed
    {
    public:
        MainPage();

    protected:
        virtual void OnManipulationDelta(Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs^ args) override;
    };
}
