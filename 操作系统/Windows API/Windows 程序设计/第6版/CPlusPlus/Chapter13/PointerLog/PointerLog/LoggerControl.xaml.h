//
// LoggerControl.xaml.h
// Declaration of the LoggerControl class
//

#pragma once

#include "LoggerControl.g.h"

namespace PointerLog
{

    public ref class LoggerControl sealed
    {
    private:

        ref struct PointerInfo
        {
        internal:
            Windows::UI::Xaml::Controls::StackPanel^ stackPanel;
            Platform::String^ repeatEvent;
            Windows::UI::Xaml::Controls::TextBlock^ repeatTextBlock;
        };

        Platform::Collections::Map<unsigned int, PointerInfo^>^ pointerDictionary;

    public:
        LoggerControl();
        property bool CaptureOnPress;
        void Clear();

    protected:
        virtual void OnPointerEntered(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args) override;
        virtual void OnPointerPressed(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args) override;
        virtual void OnPointerMoved(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args) override;
        virtual void OnPointerReleased(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args) override;
        virtual void OnPointerExited(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args) override;
        virtual void OnPointerCaptureLost(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args) override;
        virtual void OnPointerCanceled(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args) override;
        virtual void OnPointerWheelChanged(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args) override;

    private:
        void Log(Platform::String^ eventName, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args);
    };
}
