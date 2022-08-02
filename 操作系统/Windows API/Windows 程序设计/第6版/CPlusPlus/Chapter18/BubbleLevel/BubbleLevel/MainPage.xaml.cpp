//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace BubbleLevel;

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

    accelerometer = Accelerometer::GetDefault();
    DisplayProperties::AutoRotationPreferences = DisplayProperties::NativeOrientation;
    Loaded += ref new RoutedEventHandler(this, &MainPage::OnMainPageLoaded);
    SizeChanged += ref new SizeChangedEventHandler(this, &MainPage::OnMainPageSizeChanged);
}

void MainPage::OnMainPageLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args)
{
    if (accelerometer != nullptr)
    {
        accelerometer->ReportInterval = accelerometer->MinimumReportInterval;
        SetBubble(accelerometer->GetCurrentReading());
        accelerometer->ReadingChanged += 
            ref new TypedEventHandler<Accelerometer^, 
                                      AccelerometerReadingChangedEventArgs^>(this, &MainPage::OnAccelerometerReadingChanged);
    }
    else
    {
        MessageDialog^ messageDialog = ref new MessageDialog("Accelerometer is not available");
        task<IUICommand^> showDialogTask = create_task(messageDialog->ShowAsync());
        showDialogTask.then([this] (IUICommand^ command) {});
    }
}

void MainPage::OnMainPageSizeChanged(Object^ sender, SizeChangedEventArgs^ args)
{
    double size = min(args->NewSize.Width, args->NewSize.Height);
    outerCircle->Width = size;
    outerCircle->Height = size;
    halfCircle->Width = size / 2;
    halfCircle->Height = size / 2;
}

void MainPage::OnAccelerometerReadingChanged(Accelerometer^ sender,
                                             AccelerometerReadingChangedEventArgs^ args)
{
    this->Dispatcher->RunAsync(CoreDispatcherPriority::Normal, ref new DispatchedHandler([this, args]()
        {
            SetBubble(args->Reading);
        }));
}

void MainPage::SetBubble(AccelerometerReading^ accelerometerReading)
{
    if (accelerometerReading == nullptr)
        return;

    double x = accelerometerReading->AccelerationX;
    double y = accelerometerReading->AccelerationY;

    bubbleTranslate->X = -x * centeredGrid->ActualWidth / 2;
    bubbleTranslate->Y = y * centeredGrid->ActualHeight / 2;
}



