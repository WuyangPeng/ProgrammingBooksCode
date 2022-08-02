//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include <ppltasks.h>

using namespace XYSliderDemo;

using namespace Concurrency;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Devices::Geolocation;
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
    manualChange = false;

    // Initialize position of cross-hair in XYSlider
    Loaded += ref new RoutedEventHandler([this] (Object^ sender, RoutedEventArgs^ args)
    {
        Geolocator^ geolocator = ref new Geolocator();

        // Might not have permission!
        try
        {
            task<Geoposition^> getGeopositionTask(geolocator->GetGeopositionAsync());
            getGeopositionTask.then([this, geolocator](Geoposition^ position)
            {
                if (!manualChange)
                {
                    double x = (position->Coordinate->Longitude + 180) / 360;
                    double y = (90 - position->Coordinate->Latitude) / 180;
                    xySlider->Value = Point((float)x, (float)y);
                }
            });
        }
        catch (Exception^)
        {
        }
    });
}

void MainPage::OnXYSliderValueChanged(Object^ sender, Point point)
{
    int longitude = (int)(360 * point.X - 180 + 0.5);
    int latitude = (int)(90 - 180 * point.Y + 0.5);
    label->Text = "Longitude: " + longitude.ToString() + " Latitude: " + latitude.ToString();
    manualChange = true;
}