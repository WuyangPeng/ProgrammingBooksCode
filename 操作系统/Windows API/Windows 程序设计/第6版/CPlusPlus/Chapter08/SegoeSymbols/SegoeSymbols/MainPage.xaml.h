//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include "DoubleToStringHexByteConverter.h"

namespace SegoeSymbols
{
    public ref class MainPage sealed
    {
    private:
        static const int CellSize = 36;
        static const int LineLength = (CellSize + 1) * 16 + 18;

    public:
        MainPage();

    protected:
        void OnSliderValueChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs^ args);

    private:
        Windows::UI::Xaml::Media::FontFamily^ symbolFont;
        Windows::UI::Xaml::Controls::TextBlock^ txtblkColumnHeads[16];
        Windows::UI::Xaml::Controls::TextBlock^ txtblkCharacters[16][16];

        Platform::String^ ToHexString(int value, int digits);
    };
}
