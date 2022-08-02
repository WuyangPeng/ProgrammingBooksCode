//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace FingerPaint2
{
    public ref class MainPage sealed
    {
    private:
        Platform::Collections::Map<unsigned int, Windows::UI::Xaml::Shapes::Polyline^>^ pointerDictionary;

    public:
        MainPage();

    protected:
        virtual void OnPointerPressed(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args) override;
        virtual void OnPointerMoved(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args) override;
        virtual void OnPointerReleased(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args) override;
        virtual void OnPointerCaptureLost(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args) override;
        virtual void OnKeyDown(Windows::UI::Xaml::Input::KeyRoutedEventArgs^ args) override;
    };
}
