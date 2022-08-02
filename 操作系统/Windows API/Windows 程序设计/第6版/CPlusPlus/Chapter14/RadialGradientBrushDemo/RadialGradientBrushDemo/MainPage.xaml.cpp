//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace RadialGradientBrushDemo;

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

void MainPage::OnCanvasSizeChanged(Object^ sender, SizeChangedEventArgs^ args)
{
    // Canvas.Left animation
    leftAnima->To = double(args->NewSize.Width);

    // Canvas.Top animation
    rightAnima->To = double(args->NewSize.Height);
}
