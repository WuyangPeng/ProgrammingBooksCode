//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace StretchedSpiral;

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

    for (int angle = 0; angle < 3600; angle++)
    {
        double radians = 3.14159 * angle / 180;
        double radius = angle / 3.6;
        double x = 1000 + radius * sin(radians);
        double y = 1000 - radius * cos(radians);
        polyline->Points->Append(Point(float(x), float(y)));
    }
}
