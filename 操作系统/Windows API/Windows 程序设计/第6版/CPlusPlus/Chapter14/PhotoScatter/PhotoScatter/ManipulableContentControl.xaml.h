//
// ManipulableContentControl.xaml.h
// Declaration of the ManipulableContentControl class
//

#pragma once

#include "ManipulableContentControl.g.h"
#include "ManipulationManager.h"

namespace PhotoScatter
{
    public ref class ManipulableContentControl sealed
    {
    private:
        PhotoScatter::ManipulationManager^ manipulationManager;

    public:
        ManipulableContentControl(Windows::UI::Xaml::Media::CompositeTransform^ initialTransform);

    protected:
        virtual void OnManipulationStarting(Windows::UI::Xaml::Input::ManipulationStartingRoutedEventArgs^ args) override;
        virtual void OnManipulationDelta(Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs^ args) override;
    };
}
