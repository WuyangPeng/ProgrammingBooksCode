#pragma once

namespace DialSketch
{
    public ref class Dial sealed : Windows::UI::Xaml::Controls::Primitives::RangeBase
    {
    public:
        Dial();

    protected:
        virtual void OnManipulationStarting(Windows::UI::Xaml::Input::ManipulationStartingRoutedEventArgs^ args) override;
        virtual void OnManipulationDelta(Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs^ args) override;
    };
}
