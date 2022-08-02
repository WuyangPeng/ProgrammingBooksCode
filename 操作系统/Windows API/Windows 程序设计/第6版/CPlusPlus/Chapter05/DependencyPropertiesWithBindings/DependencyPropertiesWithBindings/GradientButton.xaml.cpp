//
// GradientButton.xaml.cpp
// Implementation of the GradientButton class
//

#include "pch.h"
#include "GradientButton.xaml.h"

using namespace DependencyPropertiesWithBindings;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

DependencyProperty^ GradientButton::color1Property = 
    DependencyProperty::Register("Color1", 
                                 TypeName(Color::typeid), 
                                 TypeName(GradientButton::typeid), 
                                 ref new PropertyMetadata(Colors::White));

DependencyProperty^ GradientButton::color2Property = 
    DependencyProperty::Register("Color2", 
                                 TypeName(Color::typeid), 
                                 TypeName(GradientButton::typeid),
                                 ref new PropertyMetadata(Colors::Black));

GradientButton::GradientButton()
{
    InitializeComponent();
}

DependencyProperty^ GradientButton::Color1Property::get()
{
    return color1Property;
}

DependencyProperty^ GradientButton::Color2Property::get()
{
    return color2Property;
}

Color GradientButton::Color1::get()
{
    return Color(GetValue(Color1Property));
}

void GradientButton::Color1::set(Color value)
{
    SetValue(Color1Property, value);
}

Color GradientButton::Color2::get()
{
    return Color(GetValue(Color2Property));
}

void GradientButton::Color2::set(Color value)
{
    SetValue(Color2Property, value);
}
