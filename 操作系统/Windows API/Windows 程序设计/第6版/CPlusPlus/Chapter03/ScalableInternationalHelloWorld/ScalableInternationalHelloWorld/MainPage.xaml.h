//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace ScalableInternationalHelloWorld
{
    public ref class MainPage sealed
    {
    public:
        MainPage();

    private:
        void OnDisplayPropertiesOrientationChanged(Platform::Object^ sender);
        void SetFont();
    };
}
