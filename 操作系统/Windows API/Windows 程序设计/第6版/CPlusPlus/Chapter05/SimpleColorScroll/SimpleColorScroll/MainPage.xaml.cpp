//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace SimpleColorScroll;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Globalization::NumberFormatting;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

MainPage::MainPage()
{
    InitializeComponent();
}

void MainPage::OnSliderValueChanged(Object^ sender, RangeBaseValueChangedEventArgs^ args)
{
    unsigned char r = unsigned char(redSlider->Value);
    unsigned char g = unsigned char(greenSlider->Value);
    unsigned char b = unsigned char(blueSlider->Value);

    wchar_t result[4];
    swprintf(result, 4, L"%02X", r);
    redValue->Text = ref new String(result);
    
    swprintf(result, 4, L"%02X", g);
    greenValue->Text = ref new String(result);

    swprintf(result, 4, L"%02X", b);
    blueValue->Text = ref new String(result);

    brushResult->Color = ColorHelper::FromArgb(255, r, g, b);
}
