//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace ManipulationManagerDemo;

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

    manipulationManager = ref new ManipulationManager();

    image->ManipulationMode = ManipulationModes::All &
                              ~ManipulationModes::TranslateRailsX &
                              ~ManipulationModes::TranslateRailsY;
}

void MainPage::OnManipulationDelta(ManipulationDeltaRoutedEventArgs^ args)
{
    manipulationManager->AccumulateDelta(args->Position, args->Delta);
    matrixXform->Matrix = manipulationManager->Matrix;
}
