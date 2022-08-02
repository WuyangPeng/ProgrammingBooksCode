//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace SimpleCompass;

using namespace Concurrency;
using namespace Platform;
using namespace Windows::Devices::Sensors;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Graphics::Display;
using namespace Windows::UI::Core;
using namespace Windows::UI::Popups;
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
    compass = Compass::GetDefault();
    DisplayProperties::AutoRotationPreferences = DisplayProperties::NativeOrientation;
    Loaded += ref new RoutedEventHandler(this, &MainPage::OnMainPageLoaded);
}

void MainPage::OnMainPageLoaded(Object^ sender, RoutedEventArgs^ args)
{
    if (compass != nullptr)
    {
        ShowCompassValues(compass->GetCurrentReading());
        compass->ReportInterval = compass->MinimumReportInterval;
        compass->ReadingChanged += 
            ref new TypedEventHandler<Compass^, 
                                      CompassReadingChangedEventArgs^>(this, &MainPage::OnCompassReadingChanged);
    }
    else
    {
        MessageDialog^ messageDialog = ref new MessageDialog("Compass is not available");
        task<IUICommand^> showDialogTask = create_task(messageDialog->ShowAsync());
        showDialogTask.then([this] (IUICommand^ command) {});
    }
}

void MainPage::OnCompassReadingChanged(Compass^ sender, CompassReadingChangedEventArgs^ args)
{
    this->Dispatcher->RunAsync(CoreDispatcherPriority::Normal, ref new DispatchedHandler([this, args]()
        {
            ShowCompassValues(args->Reading);
        }));
}

void MainPage::ShowCompassValues(CompassReading^ compassReading)
{
    if (compassReading == nullptr)
        return;

    magNorthRotate->Angle = -compassReading->HeadingMagneticNorth;

    if (compassReading->HeadingTrueNorth != nullptr)
    {
        trueNorthPath->Visibility = Windows::UI::Xaml::Visibility::Visible;
        trueNorthRotate->Angle = -compassReading->HeadingTrueNorth->Value;
    }
    else
    {
        trueNorthPath->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
    }
}
