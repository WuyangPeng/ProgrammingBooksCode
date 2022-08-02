#pragma once

#include "pch.h"

namespace ColorTextBoxes
{
    [Windows::UI::Xaml::Data::Bindable]
    public ref class RgbViewModel sealed : Windows::UI::Xaml::Data::INotifyPropertyChanged
    {
    private:
        double red, green, blue;
        Windows::UI::Color color;
        void Calculate();

    public:
        RgbViewModel();

        virtual event Windows::UI::Xaml::Data::PropertyChangedEventHandler^ PropertyChanged;

        property double Red
        {
            double get();
            void set(double value);
        }

        property double Green
        {
            double get();
            void set(double value);
        }

        property double Blue
        {
            double get();
            void set(double value);
        }

        property Windows::UI::Color Color
        {
            Windows::UI::Color get();
            void set(Windows::UI::Color value);
        }

    protected:
        void OnPropertyChanged(Platform::String^ propertyName);
    };
}
