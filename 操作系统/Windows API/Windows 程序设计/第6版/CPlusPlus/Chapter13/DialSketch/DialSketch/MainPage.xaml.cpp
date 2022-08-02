//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace DialSketch;

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

    Loaded += ref new RoutedEventHandler([this] (Object^ sender, RoutedEventArgs^ args)
    {
        polyline->Points->Append(Point((float)(drawingGrid->ActualWidth / 2),
                                       (float)(drawingGrid->ActualHeight / 2)));
    });
}

void MainPage::OnDialValueChanged(Object^ sender, RangeBaseValueChangedEventArgs^ args)
{
    Dial^ dial = dynamic_cast<Dial^>(sender);
    RotateTransform^ rotate = dynamic_cast<RotateTransform^>(dial->RenderTransform);
    rotate->Angle = args->NewValue;

    double xFraction = (horzDial->Value - horzDial->Minimum) / (horzDial->Maximum - horzDial->Minimum);
    double yFraction = (vertDial->Value - vertDial->Minimum) / (vertDial->Maximum - vertDial->Minimum);
    double x = xFraction * drawingGrid->ActualWidth;
    double y = yFraction * drawingGrid->ActualHeight;
    polyline->Points->Append(Point((float)x, (float)y));
}

void MainPage::OnClearButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    polyline->Points->Clear();
}


