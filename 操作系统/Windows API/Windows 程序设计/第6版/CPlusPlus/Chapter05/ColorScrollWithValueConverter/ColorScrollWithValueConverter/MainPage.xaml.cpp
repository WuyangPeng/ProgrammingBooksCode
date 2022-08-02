//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace ColorScrollWithValueConverter;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
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

    brushResult->Color = ColorHelper::FromArgb(255, r, g, b);
}

