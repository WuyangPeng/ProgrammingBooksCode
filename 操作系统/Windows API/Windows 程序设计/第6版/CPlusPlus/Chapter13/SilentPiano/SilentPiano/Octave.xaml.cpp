//
// Octave.xaml.cpp
// Implementation of the Octave class
//

#include "pch.h"
#include "Octave.xaml.h"

using namespace SilentPiano;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

DependencyProperty^ Octave::lastKeyVisibleProperty = 
    DependencyProperty::Register("LastKeyVisible", 
                                 TypeName(bool::typeid), 
                                 TypeName(Octave::typeid),
                                 ref new PropertyMetadata(false, 
                                 ref new PropertyChangedCallback(OnLastKeyVisibleChanged)));

Octave::Octave()
{
    InitializeComponent();
}

DependencyProperty^ Octave::LastKeyVisibleProperty::get()
{
    return lastKeyVisibleProperty;
}

void Octave::LastKeyVisible::set(bool angle)
{
    SetValue(LastKeyVisibleProperty, angle);
}

bool Octave::LastKeyVisible::get()
{
    return (bool)GetValue(LastKeyVisibleProperty);
}

void Octave::OnLastKeyVisibleChanged(DependencyObject^ obj, DependencyPropertyChangedEventArgs^ args)
{
    dynamic_cast<Octave^>(obj)->lastKey->Visibility = (bool)args->NewValue ? Windows::UI::Xaml::Visibility::Visible : Windows::UI::Xaml::Visibility::Collapsed;
}
