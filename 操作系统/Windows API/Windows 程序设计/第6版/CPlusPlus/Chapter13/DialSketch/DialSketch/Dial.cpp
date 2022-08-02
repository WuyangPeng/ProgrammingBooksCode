#include "pch.h"
#include "Dial.h"

using namespace DialSketch;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Input;

Dial::Dial()
{
    this->ManipulationMode = ManipulationModes::Rotate;
}

void Dial::OnManipulationStarting(ManipulationStartingRoutedEventArgs^ args)
{
    args->Pivot = ref new ManipulationPivot(Point((float)(this->ActualWidth / 2), 
                                                  (float)(this->ActualHeight / 2)), 
                                            48);
}

void Dial::OnManipulationDelta(ManipulationDeltaRoutedEventArgs^ args)
{
    this->Value = max(this->Minimum,
                  min(this->Maximum, this->Value + args->Delta.Rotation));
}
