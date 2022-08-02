//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include "XYSlider.h"

namespace XYSliderDemo
{
    public ref class MainPage sealed
    {
    private:
        bool manualChange;

    public:
        MainPage();

    private:
        void OnXYSliderValueChanged(Platform::Object^ sender, Windows::Foundation::Point point);
    };
}
