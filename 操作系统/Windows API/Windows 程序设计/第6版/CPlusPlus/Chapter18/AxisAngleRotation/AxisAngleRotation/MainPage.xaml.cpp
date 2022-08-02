//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace AxisAngleRotation;

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

    inclinometer = Inclinometer::GetDefault();
    orientationSensor = OrientationSensor::GetDefault();

    DisplayProperties::AutoRotationPreferences = DisplayProperties::NativeOrientation;
    Loaded += ref new RoutedEventHandler(this, &MainPage::OnMainPageLoaded);
}

void MainPage::OnMainPageLoaded(Object^ sender, RoutedEventArgs^ args)
{
    if (inclinometer == nullptr)
    {
        MessageDialog^ messageDialog = ref new MessageDialog("Inclinometer is not available");
        task<IUICommand^> showDialogTask = create_task(messageDialog->ShowAsync());
        showDialogTask.then([this] (IUICommand^ command) 
        {
            if (orientationSensor == nullptr)
            {
                MessageDialog^ messageDialog = ref new MessageDialog("OrientationSensor is not avaiable");
                task<IUICommand^> showDialogTask = create_task(messageDialog->ShowAsync());
                showDialogTask.then([this] (IUICommand^ command) {});
            }
        });
    }
    else if (orientationSensor == nullptr)
    {
        MessageDialog^ messageDialog = ref new MessageDialog("OrientationSensor is not avaiable");
        task<IUICommand^> showDialogTask = create_task(messageDialog->ShowAsync());
        showDialogTask.then([this] (IUICommand^ command) {});
    }

    if (inclinometer != nullptr)
    {
        ShowYawPitchRoll(inclinometer->GetCurrentReading());
        inclinometer->ReportInterval = inclinometer->MinimumReportInterval;
        inclinometer->ReadingChanged += 
            ref new TypedEventHandler<Inclinometer^, 
                                      InclinometerReadingChangedEventArgs^>(this, &MainPage::OnInclinometerReadingChanged);
    }

    if (orientationSensor != nullptr)
    {
        ShowOrientation(orientationSensor->GetCurrentReading());
        orientationSensor->ReportInterval = orientationSensor->MinimumReportInterval;
        orientationSensor->ReadingChanged += 
            ref new TypedEventHandler<OrientationSensor^, 
                                      OrientationSensorReadingChangedEventArgs^>(this, &MainPage::OnOrientationSensorChanged);
    }
}

void MainPage::OnInclinometerReadingChanged(Inclinometer^ sender, InclinometerReadingChangedEventArgs^ args)
{
    this->Dispatcher->RunAsync(CoreDispatcherPriority::Normal, ref new DispatchedHandler([this, args]()
        {
            ShowYawPitchRoll(args->Reading);
        }));
}

void MainPage::ShowYawPitchRoll(InclinometerReading^ inclinometerReading)
{
    if (inclinometerReading == nullptr)
        return;

    yawText->Text = Format(inclinometerReading->YawDegrees, 0) + "°";
    pitchText->Text = Format(inclinometerReading->PitchDegrees, 0) + "°";
    rollText->Text = Format(inclinometerReading->RollDegrees, 0) + "°";
}

void MainPage::OnOrientationSensorChanged(OrientationSensor^ sender,
                                          OrientationSensorReadingChangedEventArgs^ args)
{
    this->Dispatcher->RunAsync(CoreDispatcherPriority::Normal, ref new DispatchedHandler([this, args]()
        {
            ShowOrientation(args->Reading);
        }));
}

void MainPage::ShowOrientation(OrientationSensorReading^ orientationReading)
{
    if (orientationReading == nullptr)
        return;

    SensorRotationMatrix^ matrix = orientationReading->RotationMatrix;

    if (matrix == nullptr)
        return;

    m11Text->Text = Format(matrix->M11, 3);
    m12Text->Text = Format(matrix->M12, 3);
    m13Text->Text = Format(matrix->M13, 3);

    m21Text->Text = Format(matrix->M21, 3);
    m22Text->Text = Format(matrix->M22, 3);
    m23Text->Text = Format(matrix->M23, 3);

    m31Text->Text = Format(matrix->M31, 3);
    m32Text->Text = Format(matrix->M32, 3);
    m33Text->Text = Format(matrix->M33, 3);

    // Convert rotation matrix to axis and angle
    double angle = acos((matrix->M11 + matrix->M22 + matrix->M33 - 1) / 2);
    angleText->Text = Format(180 * angle / 3.14159, 0) + "°";

    if (angle != 0)
    {
        double twoSine = 2 * sin(angle);
        double x = (matrix->M23 - matrix->M32) / twoSine;
        double y = (matrix->M31 - matrix->M13) / twoSine;
        double z = (matrix->M12 - matrix->M21) / twoSine;

        axisText->Text = Format(x, 2) + " " + Format(y, 2) + " " + Format(z, 2);
    }
}

String^ MainPage::Format(double number, int decimals)
{
    wchar_t str[16];
    swprintf(str, sizeof(str) / sizeof(str[0]), L"%.*f", decimals, number);
    return ref new String(str);
}
