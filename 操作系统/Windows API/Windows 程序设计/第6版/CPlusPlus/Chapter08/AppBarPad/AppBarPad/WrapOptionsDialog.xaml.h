//
// WrapOptionsDialog.xaml.h
// Declaration of the WrapOptionsDialog class
//

#pragma once

#include "WrapOptionsDialog.g.h"

namespace AppBarPad
{
    [Windows::Foundation::Metadata::WebHostHidden]
    public ref class WrapOptionsDialog sealed
    {
    public:
        WrapOptionsDialog();

        static property Windows::UI::Xaml::DependencyProperty^ TextWrappingProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get();
        };

        property Windows::UI::Xaml::TextWrapping TextWrapping
        { 
            void set(Windows::UI::Xaml::TextWrapping value) { SetValue(WrapOptionsDialog::TextWrappingProperty, value); }
            Windows::UI::Xaml::TextWrapping get() { return Windows::UI::Xaml::TextWrapping(GetValue(WrapOptionsDialog::TextWrappingProperty)); }
        };

    private:
        static void OnTextWrappingChanged(Windows::UI::Xaml::DependencyObject^ sender, Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ args);
        void OnTextWrappingInstanceChanged(Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ args);
        void OnRadioButtonChecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
    };
}
