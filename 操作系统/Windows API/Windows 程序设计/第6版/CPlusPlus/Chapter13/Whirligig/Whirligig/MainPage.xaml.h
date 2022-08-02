//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace Whirligig
{
    public ref class MainPage sealed
    {
    private:
        ref struct TouchInfo
        {
        internal:
            Windows::Foundation::Point LastPoint;
            Windows::UI::Xaml::Shapes::Polyline^ Polyline;
            double Angle;
        };

        Platform::Collections::Map<unsigned int, TouchInfo^>^ pointerDictionary;

    public:
        MainPage();

    protected:
        virtual void OnPointerPressed(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args) override;
        virtual void OnPointerMoved(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args) override;
        virtual void OnPointerReleased(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args) override;
        virtual void OnPointerCaptureLost(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args) override;
    };
}
