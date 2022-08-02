#pragma once

#include "pch.h"

namespace XYSliderDemo
{
    public ref class XYSlider sealed : Windows::UI::Xaml::Controls::ContentControl
    {
    private:
        static Windows::UI::Xaml::DependencyProperty^ valueProperty;

        Windows::UI::Xaml::Controls::ContentPresenter^ contentPresenter;
        Windows::UI::Xaml::FrameworkElement^ crossHairPart;

        Windows::Foundation::EventRegistrationToken contentPresenterManipulationStartedEventToken;
        Windows::Foundation::EventRegistrationToken contentPresenterManipulationDeltaEventToken;
        Windows::Foundation::EventRegistrationToken contentPresenterSizeChangedEventToken;

    public:
        XYSlider();
        event Windows::Foundation::EventHandler<Windows::Foundation::Point>^ ValueChanged;

        static property Windows::UI::Xaml::DependencyProperty^ ValueProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get();
        }

        property Windows::Foundation::Point Value
        { 
            Windows::Foundation::Point get(); 
            void set(Windows::Foundation::Point);
        }

    protected:
        virtual void OnApplyTemplate() override;

    private:
        void OnContentPresenterManipulationStarted(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationStartedRoutedEventArgs^ args);
        void OnContentPresenterManipulationDelta(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationDeltaRoutedEventArgs^ args);
        void OnContentPresenterSizeChanged(Platform::Object^ sender, Windows::UI::Xaml::SizeChangedEventArgs^ args);
        void RecalculateValue(Windows::Foundation::Point absolutePoint);
        void SetCrossHair();
        static void OnDependencyPropertyValueChanged(Windows::UI::Xaml::DependencyObject^ obj, Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ args);

    protected:
        void OnValueChanged(Windows::Foundation::Point value);
    };
}
