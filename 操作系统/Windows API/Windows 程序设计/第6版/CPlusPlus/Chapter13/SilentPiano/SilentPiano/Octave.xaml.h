//
// Octave.xaml.h
// Declaration of the Octave class
//

#pragma once

#include "Octave.g.h"

namespace SilentPiano
{
    public ref class Octave sealed
    {
    private:
        static Windows::UI::Xaml::DependencyProperty^ lastKeyVisibleProperty;

    public:
        Octave();

        static property Windows::UI::Xaml::DependencyProperty^ LastKeyVisibleProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get();
        };

        property bool LastKeyVisible
        {
            void set(bool);
            bool get();
        };

    private:
        static void OnLastKeyVisibleChanged(Windows::UI::Xaml::DependencyObject^ sender, Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ args);
    };
}
