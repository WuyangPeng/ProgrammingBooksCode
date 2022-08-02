//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace ManualBrushAnimation;

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
    CompositionTarget::Rendering += ref new EventHandler<Object^>(this, &MainPage::OnCompositionTargetRendering);
}

void MainPage::OnCompositionTargetRendering(Object^ sender, Object^ args)
{
    RenderingEventArgs^ renderArgs = dynamic_cast<RenderingEventArgs^>(args);
    double t = 0.000000025 * renderArgs->RenderingTime.Duration;
    t -= int(t);
    t = t < 0.5 ? 2 * t : 2 - 2 * t;

    // Background
    unsigned char gray = unsigned char(255 * t);
    Color clr = ColorHelper::FromArgb(255, gray, gray, gray);
    contentGrid->Background = ref new SolidColorBrush(clr);

    // Foreground
    gray = unsigned char(255 - gray);
    clr = ColorHelper::FromArgb(255, gray, gray, gray);
    txtblk->Foreground = ref new SolidColorBrush(clr);
}
