//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace RotateAroundCenter;

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

    Loaded += ref new RoutedEventHandler( 
        [this](Object^ sender, RoutedEventArgs^ args)
    {
        rotate->CenterX = txtblk->ActualWidth / 2;
    });

    SizeChanged += ref new SizeChangedEventHandler(
        [this](Object^ sender, SizeChangedEventArgs^ args)
    {
        rotate->CenterY = args->NewSize.Height / 2;
    });
}

