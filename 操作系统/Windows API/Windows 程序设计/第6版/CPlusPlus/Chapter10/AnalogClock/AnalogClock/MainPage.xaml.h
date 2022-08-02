//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace AnalogClock
{
    public ref class MainPage sealed
    {
    public:
        MainPage();

    private:
        virtual void OnCompositionTargetRendering(Platform::Object^ sender, Platform::Object^ args);
    };
}
