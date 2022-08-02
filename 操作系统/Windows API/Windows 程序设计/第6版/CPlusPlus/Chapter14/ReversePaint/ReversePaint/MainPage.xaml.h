//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace ReversePaint
{
    public ref class MainPage sealed
    {
    private:
        Platform::Collections::Map<unsigned int, Windows::Foundation::Point>^ pointerDictionary;
        Windows::UI::Xaml::Media::Imaging::WriteableBitmap^ bitmap;
        byte* pixels;
        Windows::Foundation::Point imageOffset;
        float imageScale;

        PetzoldWindows8VectorDrawing::RoundCappedLine^ roundCappedLine;    
        Platform::Collections::Vector<float>^ xCollection;

    public:
        MainPage();

    private:
        void OnMainPageSizeChanged(Platform::Object^ sender, Windows::UI::Xaml::SizeChangedEventArgs^ args);
        void OnMainPageLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void CalculateImageScaleAndOffset();

    protected:
        virtual void OnPointerPressed(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args) override;
        virtual void OnPointerMoved(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args) override;
        virtual void OnPointerReleased(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args) override;
        virtual void OnPointerCaptureLost(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args) override;

    private:
        void RenderOnBitmap(Windows::Foundation::Point point1, Windows::Foundation::Point point2, float radius, Windows::UI::Color color);
        Windows::Foundation::Point ScaleToBitmap(Windows::Foundation::Point pt);
    };
}
