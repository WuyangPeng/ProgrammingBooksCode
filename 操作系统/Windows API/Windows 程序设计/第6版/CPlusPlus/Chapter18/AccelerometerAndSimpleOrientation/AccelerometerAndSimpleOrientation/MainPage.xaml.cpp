//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace AccelerometerAndSimpleOrientation;

using namespace Concurrency;
using namespace Platform;
using namespace Windows::Devices::Sensors;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
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
    simpleOrientationSensor = SimpleOrientationSensor::GetDefault();
    Loaded += ref new RoutedEventHandler(this, &MainPage::OnMainPageLoaded);
}

void MainPage::OnNavigatedTo(NavigationEventArgs^ args)
{
    if (accelerometer != nullptr)
    {
        SetAccelerometerText(accelerometer->GetCurrentReading());

        accelerometerEventToken = 
            accelerometer->ReadingChanged += 
                ref new TypedEventHandler<Accelerometer^, 
                                          AccelerometerReadingChangedEventArgs^>(this, &MainPage::OnAccelerometerReadingChanged);
    }

    if (simpleOrientationSensor != nullptr)
    {
        SetOrientationSensorText(simpleOrientationSensor->GetCurrentOrientation());

        orientationEventToken = 
            simpleOrientationSensor->OrientationChanged += 
                ref new TypedEventHandler<SimpleOrientationSensor^, 
                                          SimpleOrientationSensorOrientationChangedEventArgs^>(this, &MainPage::OnSimpleOrientationChanged);
    }
}

void MainPage::OnNavigatedFrom(NavigationEventArgs^ args)
{
    if (accelerometer != nullptr)
        accelerometer->ReadingChanged -= accelerometerEventToken;

    if (simpleOrientationSensor != nullptr)
        simpleOrientationSensor->OrientationChanged -= orientationEventToken;
}

void MainPage::OnMainPageLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args)
{
    if (accelerometer == nullptr)
    {
        MessageDialog^ messageDialog = ref new MessageDialog("Cannot start Accelerometer");
        task<IUICommand^> showDialogTask = create_task(messageDialog->ShowAsync());
        showDialogTask.then([this] (IUICommand^ command) 
        {
            if (simpleOrientationSensor == nullptr)
            {
                MessageDialog^ messageDialog = ref new MessageDialog("Cannot start SimpleOrientationSensor");
                task<IUICommand^> showDialogTask = create_task(messageDialog->ShowAsync());
                showDialogTask.then([] (IUICommand^ command) {});
            }
        });
    }
    else if (simpleOrientationSensor == nullptr)
    {
        MessageDialog^ messageDialog = ref new MessageDialog("Cannot start SimpleOrientationSensor");
        task<IUICommand^> showDialogTask = create_task(messageDialog->ShowAsync());
        showDialogTask.then([] (IUICommand^ command) {});
    }
}

void MainPage::OnAccelerometerReadingChanged(Accelerometer^ sender,
                                             AccelerometerReadingChangedEventArgs^ args)
{
    this->Dispatcher->RunAsync(CoreDispatcherPriority::Normal, ref new DispatchedHandler([this, args]()
        {
            SetAccelerometerText(args->Reading);
        }));
}

void MainPage::SetAccelerometerText(AccelerometerReading^ accelerometerReading)
{
    if (accelerometerReading == nullptr)
        return;

    accelerometerX->Text = Format(accelerometerReading->AccelerationX, 2);
    accelerometerY->Text = Format(accelerometerReading->AccelerationY, 2);
    accelerometerZ->Text = Format(accelerometerReading->AccelerationZ, 2);
    magnitude->Text = Format(sqrt(pow(accelerometerReading->AccelerationX, 2) +
                                  pow(accelerometerReading->AccelerationY, 2) +
                                  pow(accelerometerReading->AccelerationZ, 2)), 2);
}

String^ MainPage::Format(double number, int decimals)
{
    wchar_t str[16];
    swprintf(str, sizeof(str) / sizeof(str[0]), L"%.*f", decimals, number);
    return ref new String(str);
}

// SimpleOrientationSensor handler
void MainPage::OnSimpleOrientationChanged(SimpleOrientationSensor^ sender, 
                                          SimpleOrientationSensorOrientationChangedEventArgs^ args)
{
    this->Dispatcher->RunAsync(CoreDispatcherPriority::Normal, ref new DispatchedHandler([this, args]()
        {
            SetOrientationSensorText(args->Orientation);
        }));
}

void MainPage::SetOrientationSensorText(SimpleOrientation simpleOrientation)
{
    this->simpleOrientation->Text = simpleOrientation.ToString();
}
