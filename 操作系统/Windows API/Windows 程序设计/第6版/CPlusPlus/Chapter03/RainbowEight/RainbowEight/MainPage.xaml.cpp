//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace RainbowEight;

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
    this->Loaded += ref new RoutedEventHandler(this, &MainPage::OnPageLoaded);
}

void MainPage::OnPageLoaded(Object^ sender, RoutedEventArgs^ args)
{
    txtblkBaseSize = txtblk->ActualHeight;
    CompositionTarget::Rendering += ref new EventHandler<Object^>(this, &MainPage::OnCompositionTargetRendering);
}

void MainPage::OnCompositionTargetRendering(Object^ sender, Object^ args)
{
    // Set FontSize as large as it can be
    txtblk->FontSize = this->ActualHeight / txtblkBaseSize;

    // Calculate t from 0 to 1 repetitively
    RenderingEventArgs^ renderArgs = dynamic_cast<RenderingEventArgs^>(args);
    double t = 0.000000025 * renderArgs->RenderingTime.Duration;
    t -= int(t);

    // Loop through GradientStop objects
    for (unsigned int index = 0; index < gradientBrush->GradientStops->Size; index++)
        gradientBrush->GradientStops->GetAt(index)->Offset = index / 7.0 - t;
}
