//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace FingerPaint5
{
    public ref class MainPage sealed
    {
    private:
        ref struct PointerInfo
        {
        internal:
            Windows::UI::Xaml::Media::Brush^ Brush;
            Windows::Foundation::Point PreviousPoint;
            float PreviousRadius;
        };

        Platform::Collections::Map<unsigned int, PointerInfo^>^ pointerDictionary;

    public:
        MainPage();

    protected:
        virtual void OnPointerPressed(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args) override;
        virtual void OnPointerMoved(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args) override;
        virtual void OnPointerReleased(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args) override;
        virtual void OnPointerCaptureLost(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args) override;

    private:
        Windows::UI::Xaml::Media::Geometry^ CreateTaperedLineGeometry(Windows::Foundation::Point c0, float r0,
                                                                      Windows::Foundation::Point c1, float r1);
    };
}
