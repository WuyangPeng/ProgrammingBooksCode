//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace RotationCenterDemo;

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

    Loaded += ref new RoutedEventHandler([this](Object^ sender, RoutedEventArgs^ args)
        {
            translate->X = txtblk->ActualWidth / 2;
            translateBack1->X = -translate->X;
            translateBack2->X = -translate->X;
            translateBack3->X = -translate->X;

            translate->Y = txtblk->ActualHeight / 2;
            translateBack1->Y = -translate->Y;
            translateBack2->Y = -translate->Y;
            translateBack3->Y = -translate->Y;
        });
}

