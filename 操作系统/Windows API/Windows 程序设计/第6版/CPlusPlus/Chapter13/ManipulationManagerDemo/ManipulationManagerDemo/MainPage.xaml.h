//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include "ManipulationManager.h"

namespace ManipulationManagerDemo
{
    public ref class MainPage sealed
    {
    private:
        ManipulationManagerDemo::ManipulationManager^ manipulationManager;

    public:
        MainPage();

    protected:
        virtual void OnManipulationDelta(Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs^ args) override;
    };
}
