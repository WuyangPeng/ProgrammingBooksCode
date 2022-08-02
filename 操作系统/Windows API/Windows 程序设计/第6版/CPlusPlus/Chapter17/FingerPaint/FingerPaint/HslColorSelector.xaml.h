//
// HslColorSelector.xaml.h
// Declaration of the HslColorSelector class
//

#pragma once

#include "HslColorSelector.g.h"
#include "XYSlider.h"

namespace FingerPaint
{
    [Windows::Foundation::Metadata::WebHostHidden]
    public ref class HslColorSelector sealed
    {
    private:
        bool doNotSetSliders;
        static Windows::UI::Xaml::DependencyProperty^ colorProperty;

    public:
        HslColorSelector();
        event Windows::Foundation::EventHandler<Windows::UI::Color>^ ColorChanged;

        static property Windows::UI::Xaml::DependencyProperty^ ColorProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get() { return colorProperty; }
        }

        property Windows::UI::Color Color
        {
            void set(Windows::UI::Color value) { SetValue(HslColorSelector::ColorProperty, value); }
            Windows::UI::Color get() { return (Windows::UI::Color)GetValue(HslColorSelector::ColorProperty); }
        }

    private:
        void OnLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnXYSliderValueChanged(Platform::Object^ sender, Windows::Foundation::Point point);
        void OnSliderValueChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs^ args);
        void SetColorFromSliders();
        static void OnColorChangedStatic(Windows::UI::Xaml::DependencyObject^ obj, Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ args);
        Windows::UI::Color HslToRgb(int h, int s, int l);
        void RgbToHsl(Windows::UI::Color, int *ph, int *ps, int *pl);
        
    protected:
        virtual void OnColorChanged(Windows::UI::Color color);
    };
}
