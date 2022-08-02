//
// ManipulableContentControl.xaml.cpp
// Implementation of the ManipulableContentControl class
//

#include "pch.h"
#include "ManipulableContentControl.xaml.h"

using namespace PhotoScatter;

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

ManipulableContentControl::ManipulableContentControl(CompositeTransform^ initialTransform)
{
    InitializeComponent();

    // Create the ManipulationManager and set MatrixTransform from it
    manipulationManager = ref new ManipulationManager(initialTransform);
    matrixXform->Matrix = manipulationManager->Matrix;

    this->ManipulationMode = ManipulationModes::All &
                            ~ManipulationModes::TranslateRailsX &
                            ~ManipulationModes::TranslateRailsY;
}

void ManipulableContentControl::OnManipulationStarting(ManipulationStartingRoutedEventArgs^ args)
{
    static int zIndex = 0;

    Canvas::SetZIndex(this, zIndex += 1);
}

void ManipulableContentControl::OnManipulationDelta(ManipulationDeltaRoutedEventArgs^ args)
{
    manipulationManager->AccumulateDelta(args->Position, args->Delta);
    matrixXform->Matrix = manipulationManager->Matrix;
}

