//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace RainbowEight
{
    public ref class MainPage sealed
    {
    private:
        double txtblkBaseSize;    // ie, for 1-pixel FontSize

    public:
        MainPage();

    private:
        void OnPageLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnCompositionTargetRendering(Platform::Object^ sender, Platform::Object^ args);
    };
}
