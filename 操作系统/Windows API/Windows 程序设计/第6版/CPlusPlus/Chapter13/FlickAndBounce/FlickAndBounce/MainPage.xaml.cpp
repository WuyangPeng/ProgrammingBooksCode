//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace FlickAndBounce;

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
}

void MainPage::OnEllipseManipulationStarted(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationStartedRoutedEventArgs^ args)
{
    // Initialize directions
    xDirection = 1;
    yDirection = 1;
}

void MainPage::OnEllipseManipulationDelta(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs^ args)
{
    // Find new position of ellipse regardless of edges
    double x = Canvas::GetLeft(ellipse) + xDirection * args->Delta.Translation.X;
    double y = Canvas::GetTop(ellipse) + yDirection * args->Delta.Translation.Y;

    if (args->IsInertial)
    {
        // Bounce it off the edges
        Size playground = Size((float)(contentGrid->ActualWidth - ellipse->Width),
                               (float)(contentGrid->ActualHeight - ellipse->Height));

        while (x < 0 || y < 0 || x > playground.Width || y > playground.Height)
        {
            if (x < 0)
            {
                x = -x;
                xDirection *= -1;
            }
            if (x > playground.Width)
            {
                x = 2 * playground.Width - x;
                xDirection *= -1;
            }
            if (y < 0)
            {
                y = -y;
                yDirection *= -1;
            }
            if (y > playground.Height)
            {
                y = 2 * playground.Height - y;
                yDirection *= -1;
            }
        }
    }
    Canvas::SetLeft(ellipse, x);
    Canvas::SetTop(ellipse, y);
}

void MainPage::OnEllipseManipulationInertiaStarting(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationInertiaStartingRoutedEventArgs^ args)
{
    double maxVelocity = max(abs(args->Velocities.Linear.X), 
                             abs(args->Velocities.Linear.Y));
    args->TranslationBehavior->DesiredDeceleration = maxVelocity / (1000 * slider->Value);
}
