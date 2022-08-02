//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace OrientationAndOrientation;

using namespace Platform;
using namespace Windows::Devices::Sensors;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Graphics::Display;
using namespace Windows::UI::Core;
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

    simpleOrientationSensor = SimpleOrientationSensor::GetDefault();

    // SimpleOrientationSensor initialization
    if (simpleOrientationSensor != nullptr)
    {
        SetOrientationSensorText(simpleOrientationSensor->GetCurrentOrientation());
        simpleOrientationSensor->OrientationChanged += 
            ref new TypedEventHandler<SimpleOrientationSensor^, 
                                      SimpleOrientationSensorOrientationChangedEventArgs^>(this, &MainPage::OnSimpleOrientationChanged);
    }

    // DisplayProperties initialization
    SetDisplayOrientationText(DisplayProperties::CurrentOrientation);
    DisplayProperties::OrientationChanged += 
        ref new DisplayPropertiesEventHandler(this, &MainPage::OnDisplayPropertiesOrientationChanged);
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
    orientationSensorTextBlock->Text = simpleOrientation.ToString();
}

// DisplayProperties handler
void MainPage::OnDisplayPropertiesOrientationChanged(Object^ sender)
{
    SetDisplayOrientationText(DisplayProperties::CurrentOrientation);
}

void MainPage::SetDisplayOrientationText(DisplayOrientations displayOrientation)
{
    displayOrientationTextBlock->Text = displayOrientation.ToString();
}
