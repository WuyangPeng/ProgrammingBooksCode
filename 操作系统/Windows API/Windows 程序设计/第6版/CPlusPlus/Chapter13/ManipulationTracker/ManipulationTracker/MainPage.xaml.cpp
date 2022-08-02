//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace ManipulationTracker;

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
using namespace Windows::UI::Xaml::Shapes;

MainPage::MainPage()
{
    InitializeComponent();
}

void MainPage::OnManipulationModeCheckBoxChecked(Object^ sender, RoutedEventArgs^ args)
{
    // Get composite ManipulationModes value of checked CheckBoxes
    int manipulationModes = 0;

    for(unsigned int i = 0; i < checkBoxPanel->Children->Size; i++)
    {
        ManipulationModeCheckBox^ checkBox = dynamic_cast<ManipulationModeCheckBox^>(checkBoxPanel->Children->GetAt(i));

        if (checkBox->IsChecked->Value)
            manipulationModes |= (int)checkBox->ManipulationModes;
    }

    // Set ManipulationMode property of each Rectangle
    for each (UIElement^ child in rectanglePanel->Children)
        child->ManipulationMode = (ManipulationModes)manipulationModes;
}

void MainPage::OnManipulationDelta(ManipulationDeltaRoutedEventArgs^ args)
{
    // OriginalSoruce is always Rectangle because nothing else has it
    //      ManipulationMode set to anything other than ManipulationModes.None
    Rectangle^ rectangle = dynamic_cast<Rectangle^>(args->OriginalSource);
    CompositeTransform^ transform = dynamic_cast<CompositeTransform^>(rectangle->RenderTransform);

    transform->TranslateX += args->Delta.Translation.X;
    transform->TranslateY += args->Delta.Translation.Y;

    transform->ScaleX *= args->Delta.Scale;
    transform->ScaleY *= args->Delta.Scale;

    transform->Rotation += args->Delta.Rotation;
}


