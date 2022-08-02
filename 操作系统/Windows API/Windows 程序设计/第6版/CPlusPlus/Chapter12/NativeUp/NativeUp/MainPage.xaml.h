//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace NativeUp
{
    public ref class MainPage sealed
    {
    public:
        MainPage();

    private:
        void OnOrientationChanged(Platform::Object^ sender);
        void SetRotation();
        int Log2(Windows::Graphics::Display::DisplayOrientations orientation);
    };
}
