//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace TiltAndRoll;

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
    DisplayProperties::AutoRotationPreferences = DisplayProperties::NativeOrientation;
    accelerometer = Accelerometer::GetDefault();

    ball->RadiusX = BALL_RADIUS;
    ball->RadiusY = BALL_RADIUS;

    Loaded += ref new RoutedEventHandler(this, &MainPage::OnMainPageLoaded);
}

void MainPage::OnMainPageLoaded(Object^ sender, RoutedEventArgs^ args)
{
    if (accelerometer == nullptr)
    {
        MessageDialog^ messageDialog = ref new MessageDialog("Accelerometer is not available");
        task<IUICommand^> showDialogTask = create_task(messageDialog->ShowAsync());
        showDialogTask.then([this] (IUICommand^ command) {});
    }
    else
    {
        CompositionTarget::Rendering += ref new EventHandler<Object^>(this, &MainPage::OnCompositionTargetRendering);
    }
}

void MainPage::OnCompositionTargetRendering(Object^ sender, Object^ args)
{
    AccelerometerReading^ reading = accelerometer->GetCurrentReading();

    if (reading != nullptr)
    {
        // Get elapsed time since last event
        TimeSpan timeSpan = dynamic_cast<RenderingEventArgs^>(args)->RenderingTime;
        float elapsedSeconds = (timeSpan.Duration - this->timeSpan.Duration) / 10000000.0f;
        this->timeSpan = timeSpan;

        // Convert Accelerometer reading to display coordinates
        double x = reading->AccelerationX;
        double y = -reading->AccelerationY;

        // Get current X-Y acceleration and smooth it
        D2D1_VECTOR_2F newAcceleration = { float(x), float(y) };
        acceleration.x = 0.5f * (acceleration.x + newAcceleration.x);
        acceleration.y = 0.5f * (acceleration.y + newAcceleration.y);

        // Calculate new velocity and position
        ballVelocity.x += float(GRAVITY) * acceleration.x * elapsedSeconds;
        ballVelocity.y += float(GRAVITY) * acceleration.y * elapsedSeconds;
        ballPosition.x += ballVelocity.x * elapsedSeconds;
        ballPosition.y += ballVelocity.y * elapsedSeconds;

        // Check for hitting edge
        if (ballPosition.x - BALL_RADIUS < 0)
        {
            ballPosition.x = float(BALL_RADIUS);
            ballVelocity.x = 0;
        }
        if (ballPosition.x + BALL_RADIUS > this->ActualWidth)
        {
            ballPosition.x = float(this->ActualWidth) - BALL_RADIUS;
            ballVelocity.x = 0;
        }
        if (ballPosition.y - BALL_RADIUS < 0)
        {
            ballPosition.y = float(BALL_RADIUS);
            ballVelocity.y = 0;
        }
        if (ballPosition.y + BALL_RADIUS > this->ActualHeight)
        {
            ballPosition.y = float(this->ActualHeight) - BALL_RADIUS;
            ballVelocity.y = 0;
        }
        ball->Center = Point(ballPosition.x, ballPosition.y);
    }
}


