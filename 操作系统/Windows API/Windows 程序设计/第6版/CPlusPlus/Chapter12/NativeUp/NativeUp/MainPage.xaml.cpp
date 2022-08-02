//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace NativeUp;

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

    SetRotation();
    DisplayProperties::OrientationChanged += ref new DisplayPropertiesEventHandler(this, &MainPage::OnOrientationChanged);
}

void MainPage::OnOrientationChanged(Object^ sender)
{
    SetRotation();
}

void MainPage::SetRotation()
{
    rotate->Angle = 90 * (Log2(DisplayProperties::CurrentOrientation) -
                          Log2(DisplayProperties::NativeOrientation));
}

int MainPage::Log2(DisplayOrientations orientation)
{
    int value = (int)orientation;
    int log = 0;
    
    while (value > 0 && (value & 1) == 0)
    {
        value >>= 1;
        log += 1;
    }
    return log;
}
