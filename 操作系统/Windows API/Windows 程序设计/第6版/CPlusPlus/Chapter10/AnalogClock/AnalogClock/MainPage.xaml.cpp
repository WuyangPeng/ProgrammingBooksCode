//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"                    // includes Windows.h
#include "MainPage.xaml.h"

using namespace AnalogClock;

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
    CompositionTarget::Rendering += ref new EventHandler<Object^>(this, &MainPage::OnCompositionTargetRendering);
}

void MainPage::OnCompositionTargetRendering(Object^ sender, Object^ args)
{
    SYSTEMTIME dt;
    GetLocalTime(&dt);
    rotateSecond->Angle = 6 * (dt.wSecond + dt.wMilliseconds / 1000.0);
    rotateMinute->Angle = 6 * dt.wMinute + rotateSecond->Angle / 60;
    rotateHour->Angle = 30 * (dt.wHour % 12) + rotateMinute->Angle / 12;
}
