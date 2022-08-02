//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace YawPitchRoll;

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
    DisplayProperties::AutoRotationPreferences = DisplayProperties::NativeOrientation;
    Loaded += ref new RoutedEventHandler(this, &MainPage::OnMainPageLoaded);
}

void MainPage::OnMainPageLoaded(Object^ sender, RoutedEventArgs^ args)
{
    if (inclinometer == nullptr)
    {
        MessageDialog^ messageDialog = ref new MessageDialog("Cannot obtain Inclinometer");
        task<IUICommand^> showDialogTask = create_task(messageDialog->ShowAsync());
        showDialogTask.then([this] (IUICommand^ command) {});
    }
    else
    {
        ShowYawPitchRoll(inclinometer->GetCurrentReading());
        inclinometer->ReportInterval = inclinometer->MinimumReportInterval;
        inclinometer->ReadingChanged += 
            ref new TypedEventHandler<Inclinometer^, 
                                      InclinometerReadingChangedEventArgs^>(this, &MainPage::OnInclinometerReadingChanged);
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

    float yaw = inclinometerReading->YawDegrees;
    float pitch = inclinometerReading->PitchDegrees;
    float roll = inclinometerReading->RollDegrees;

    yawValue->Text = Format(yaw, 0) + "°";
    pitchValue->Text = Format(pitch, 0) + "°";
    rollValue->Text = Format(roll, 0) + "°";

    yawRotate->Angle = yaw;

    if (pitch <= 90 && pitch >= -90)
    {
        pitchPath->Fill = pitchPath->Stroke;
        pitchEllipse->Center = Point(float(this->ActualWidth / 2),
                                     float(this->ActualHeight * (pitch + 90) / 180));
    }
    else
    {
        pitchPath->Fill = nullptr;

        if (pitch > 90)
            pitchEllipse->Center = Point(float(this->ActualWidth / 2),
                                         float(this->ActualHeight * (270 - pitch) / 180));

        else // pitch < -90
            pitchEllipse->Center = Point(float(this->ActualWidth / 2),
                                         float(this->ActualHeight * (-90 - pitch) / 180));
    }
    rollEllipse->Center = Point(float(this->ActualWidth * (roll + 90) / 180),
                                float(this->ActualHeight / 2));
}

String^ MainPage::Format(double number, int decimals)
{
    wchar_t str[16];
    swprintf(str, sizeof(str) / sizeof(str[0]), L"%.*f", decimals, number);
    return ref new String(str);
}
