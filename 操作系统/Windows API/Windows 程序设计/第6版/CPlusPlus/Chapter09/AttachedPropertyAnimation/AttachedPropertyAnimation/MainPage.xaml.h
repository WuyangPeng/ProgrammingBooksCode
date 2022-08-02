//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace AttachedPropertyAnimation
{
    public ref class MainPage sealed
    {
    public:
        MainPage();

    private:
        void OnCanvasSizeChanged(Platform::Object^ sender, Windows::UI::Xaml::SizeChangedEventArgs^ args);
    };
}
