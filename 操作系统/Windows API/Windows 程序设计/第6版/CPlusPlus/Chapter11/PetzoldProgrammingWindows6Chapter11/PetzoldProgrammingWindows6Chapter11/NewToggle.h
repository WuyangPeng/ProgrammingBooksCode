//
// NewToggle.h
// Declaration of the NewToggle class.
//

#pragma once

#include "UniformGrid.h"

namespace PetzoldProgrammingWindows6Chapter11
{
    [Windows::Foundation::Metadata::WebHostHidden]
    public ref class NewToggle sealed : public Windows::UI::Xaml::Controls::ContentControl
    {
    private:
        static Windows::UI::Xaml::DependencyProperty^ checkedContentProperty;
        static Windows::UI::Xaml::DependencyProperty^ isCheckedProperty;

        Windows::UI::Xaml::Controls::Button^ uncheckButton;
        Windows::UI::Xaml::Controls::Button^ checkButton;

        Windows::Foundation::EventRegistrationToken uncheckClickEventToken, checkClickEventToken;

    public:
        NewToggle();

        event Windows::Foundation::EventHandler<Platform::Object^>^ CheckedChanged;

        static property Windows::UI::Xaml::DependencyProperty^ CheckedContentProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get() { return checkedContentProperty; }
        }

        static property Windows::UI::Xaml::DependencyProperty^ IsCheckedProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get() { return isCheckedProperty; }
        }

        property Platform::Object^ CheckedContent
        {
            void set(Platform::Object^ value) { SetValue(CheckedContentProperty, value); }
            Platform::Object^ get() { return GetValue(CheckedContentProperty); }
        }

        property bool IsChecked
        {
            void set(bool value) { SetValue(IsCheckedProperty, value); }
            bool get() { return (bool)GetValue(IsCheckedProperty); }
        }

    protected:
        virtual void OnApplyTemplate() override;
        virtual void OnCheckedChanged(Platform::Object^ args);

    private:
        void OnButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        static void OnCheckedChangedStatic(Windows::UI::Xaml::DependencyObject^ obj,
                                           Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ args);


    };
}
