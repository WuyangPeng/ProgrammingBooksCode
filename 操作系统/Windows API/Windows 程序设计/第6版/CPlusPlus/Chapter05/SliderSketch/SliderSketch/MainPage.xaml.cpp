//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace SliderSketch;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
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

void MainPage::OnBorderSizeChanged(Object^ sender, SizeChangedEventArgs^ args)
{
    Border^ border = dynamic_cast<Border^>(sender);
    xSlider->Maximum = args->NewSize.Width - border->Padding.Left 
                                           - border->Padding.Right
                                           - polyline->StrokeThickness;

    ySlider->Maximum = args->NewSize.Height- border->Padding.Top 
                                           - border->Padding.Bottom
                                           - polyline->StrokeThickness;
}

void MainPage::OnSliderValueChanged(Object^ sender, RangeBaseValueChangedEventArgs^ args)
{
    polyline->Points->Append(Point((float)xSlider->Value, (float)ySlider->Value));
}
