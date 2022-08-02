//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace BerniceBobsHerHair
{
    public ref class MainPage sealed
    {
    public:
        MainPage();

    private:
        void OnRichTextBlockSizeChanged(Platform::Object^ sender, Windows::UI::Xaml::SizeChangedEventArgs^ args);
    };
}
