//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace SilasMarner
{
    public ref class MainPage sealed
    {
    private:
        double fractionRead;

    public:
        MainPage();

    private:
        void OnFlipViewSizeChanged(Platform::Object^ sender, Windows::UI::Xaml::SizeChangedEventArgs^ args);
        void InitializeControls(double saveFractionRead);
        void OnFlipViewSelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ args);
        void OnPageSliderValueChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs^ args);
    };
}
