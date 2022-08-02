#include "pch.h"
#include "GradientButton.h"

using namespace DependencyProperties;

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
                                 ref new PropertyMetadata(Colors::White,
                                 ref new PropertyChangedCallback(GradientButton::OnColorChanged)));

DependencyProperty^ GradientButton::color2Property = 
    DependencyProperty::Register("Color2", 
                                 TypeName(Color::typeid), 
                                 TypeName(GradientButton::typeid), 
                                 ref new PropertyMetadata(Colors::Black,
                                 ref new PropertyChangedCallback(GradientButton::OnColorChanged)));

GradientButton::GradientButton()
{
    gradientStop1 = ref new GradientStop();
    gradientStop1->Offset = 0;
    gradientStop1->Color = this->Color1;

    gradientStop2 = ref new GradientStop();
    gradientStop2->Offset = 1;
    gradientStop2->Color = this->Color2;

    LinearGradientBrush^ brush = ref new LinearGradientBrush();
    brush->GradientStops->Append(gradientStop1);
    brush->GradientStops->Append(gradientStop2);

    this->Foreground = brush;
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

void GradientButton::OnColorChanged(DependencyObject^ sender, DependencyPropertyChangedEventArgs^ args)
{
    dynamic_cast<GradientButton^>(sender)->OnColorChangedInstance(args);
}

void GradientButton::OnColorChangedInstance(DependencyPropertyChangedEventArgs^ args)
{
    if (args->Property == GradientButton::Color1Property)
        gradientStop1->Color = Color(args->NewValue);

    if (args->Property == GradientButton::Color2Property)
        gradientStop2->Color = Color(args->NewValue);
}

