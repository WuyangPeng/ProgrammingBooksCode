//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace AttachedPropertyAnimation;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Media::Animation;
using namespace Windows::UI::Xaml::Navigation;

MainPage::MainPage()
{
    InitializeComponent();

    Loaded += ref new RoutedEventHandler([this] (Object^ sender, RoutedEventArgs^ args)
        {
            dynamic_cast<Storyboard^>(this->Resources->Lookup("storyboard"))->Begin();
        });
}

void MainPage::OnCanvasSizeChanged(Object^ sender, SizeChangedEventArgs^ args)
{
    Storyboard^ storyboard = dynamic_cast<Storyboard^>(this->Resources->Lookup("storyboard"));

    // Canvas.Left animation
    DoubleAnimation^ anima = dynamic_cast<DoubleAnimation^>(storyboard->Children->GetAt(0));
    anima->To = (double)args->NewSize.Width;

    // Canvas.Top animation
    anima = dynamic_cast<DoubleAnimation^>(storyboard->Children->GetAt(1));
    anima->To = (double)args->NewSize.Height;
}
