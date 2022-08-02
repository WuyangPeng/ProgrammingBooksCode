//
// GradientButton.xaml.h
// Declaration of the GradientButton class
//

#pragma once

#include "pch.h"
#include "GradientButton.g.h"

namespace DependencyPropertiesWithBindings
{
    public ref class GradientButton sealed
    {
    private:
        static Windows::UI::Xaml::DependencyProperty^ color1Property;
        static Windows::UI::Xaml::DependencyProperty^ color2Property;

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
    };
}
