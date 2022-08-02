#pragma once

#include "pch.h"

namespace FingerPaint
{
    public ref class XYSlider sealed : Windows::UI::Xaml::Controls::ContentControl
    {
    private:
        static Windows::UI::Xaml::DependencyProperty^ valueProperty;

        Windows::UI::Xaml::Controls::ContentPresenter^ contentPresenter;
        Windows::UI::Xaml::FrameworkElement^ crossHairPart;

        Windows::Foundation::EventRegistrationToken contentPresenterPointerPressedEventToken;
        Windows::Foundation::EventRegistrationToken contentPresenterPointerMovedEventToken;
        Windows::Foundation::EventRegistrationToken contentPresenterPointerReleasedEventToken;
        Windows::Foundation::EventRegistrationToken contentPresenterPointerCaptureLostEventToken;

        Windows::Foundation::EventRegistrationToken contentPresenterSizeChangedEventToken;

        Platform::Collections::Map<unsigned int, Windows::Foundation::Point>^ pointerDictionary;

    public:
        XYSlider();
        event Windows::Foundation::EventHandler<Windows::Foundation::Point>^ ValueChanged;

        static property Windows::UI::Xaml::DependencyProperty^ ValueProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get() { return valueProperty; }
        }

        property Windows::Foundation::Point Value
        { 
            Windows::Foundation::Point get() 
            { 
                return (Windows::Foundation::Point)GetValue(XYSlider::ValueProperty); 
            } 
            void set(Windows::Foundation::Point value)
            {
                SetValue(XYSlider::ValueProperty, value);
            }
        }

    protected:
        virtual void OnApplyTemplate() override;

    private:
        void OnContentPresenterPointerPressed(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args);
        void OnContentPresenterPointerMoved(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args);
        void OnContentPresenterPointerReleased(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args);

        void OnContentPresenterSizeChanged(Platform::Object^ sender, Windows::UI::Xaml::SizeChangedEventArgs^ args);
        void RecalculateValue();
        void RecalculateValue(Windows::Foundation::Point absolutePoint);
        void SetCrossHair();
        static void OnDependencyPropertyValueChanged(Windows::UI::Xaml::DependencyObject^ obj, Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ args);

    protected:
        void OnValueChanged(Windows::Foundation::Point value);
    };
}
