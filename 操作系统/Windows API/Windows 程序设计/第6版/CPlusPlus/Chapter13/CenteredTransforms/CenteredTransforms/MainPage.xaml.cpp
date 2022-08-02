//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace CenteredTransforms;

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
    image->ManipulationMode = ManipulationModes::All &
                              ~ManipulationModes::TranslateRailsX &
                              ~ManipulationModes::TranslateRailsY;
}

void MainPage::OnManipulationDelta(ManipulationDeltaRoutedEventArgs^ args)
{
    // Make this the entire transform to date
    matrixXform->Matrix = xformGroup->Value;

    // Use that to transform the Position property
    Point center = matrixXform->TransformPoint(args->Position);

    // That becomes the center of the new incremental transform
    compositeXform->CenterX = center.X;
    compositeXform->CenterY = center.Y;

    // Set the other properties
    compositeXform->TranslateX = args->Delta.Translation.X;
    compositeXform->TranslateY = args->Delta.Translation.Y;
    compositeXform->ScaleX = args->Delta.Scale;
    compositeXform->ScaleY = args->Delta.Scale;
    compositeXform->Rotation = args->Delta.Rotation;
}
