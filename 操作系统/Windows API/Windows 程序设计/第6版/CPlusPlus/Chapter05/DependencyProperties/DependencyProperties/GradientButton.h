//
// Block.xaml.h
// Declaration of the Block class
#pragma once

#include "pch.h"

namespace DependencyProperties
{
    public ref class GradientButton sealed : Windows::UI::Xaml::Controls::Button
    {
    private:
        static Windows::UI::Xaml::DependencyProperty^ color1Property;
        static Windows::UI::Xaml::DependencyProperty^ color2Property;

        Windows::UI::Xaml::Media::GradientStop^ gradientStop1;
        Windows::UI::Xaml::Media::GradientStop^ gradientStop2;

    public:
        GradientButton();

        static property Windows::UI::Xaml::DependencyProperty^ Color1Property
        {
            Windows::UI::Xaml::DependencyProperty^ get();
        }

        static property Windows::UI::Xaml::DependencyProperty^ Color2Property
        {
            Windows::UI::Xaml::DependencyProperty^ get();
        }

        property Windows::UI::Color Color1
        { 
            Windows::UI::Color get(); 
            void set(Windows::UI::Color);
        }

        property Windows::UI::Color Color2
        { 
            Windows::UI::Color get(); 
            void set(Windows::UI::Color);
        }

        static void OnColorChanged(Windows::UI::Xaml::DependencyObject^ sender, Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ args);

    private:
        void OnColorChangedInstance(Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ args);
    };
}
