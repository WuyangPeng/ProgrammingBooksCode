//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace ScalableInternationalHelloWorld;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Graphics::Display;
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
    SetFont();
    DisplayProperties::OrientationChanged += 
        ref new DisplayPropertiesEventHandler(this, &MainPage::OnDisplayPropertiesOrientationChanged);
}

void MainPage::OnDisplayPropertiesOrientationChanged(Object^ sender)
{
    SetFont();
}

void MainPage::SetFont()
{
    bool isLandscape = 
        DisplayProperties::CurrentOrientation == DisplayOrientations::Landscape ||
        DisplayProperties::CurrentOrientation == DisplayOrientations::LandscapeFlipped;

    this->FontSize = isLandscape ? 40 : 24;
}