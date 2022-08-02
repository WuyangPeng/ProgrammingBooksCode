//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include "SurfaceImageSourceRenderer.h"

namespace SpinPaint
{
    public ref class MainPage sealed
    {
    private:
        ref struct FingerInfo
            {
            internal:
                Windows::Foundation::Point ThisPosition;
                Windows::Foundation::Point LastPosition;
            };

        SurfaceImageSourceRenderer^ surfaceImageSourceRenderer;
        Windows::UI::Xaml::Media::RotateTransform^ inverseRotate;
        Platform::Collections::Map<unsigned int, FingerInfo^>^ fingerTouches;
        Platform::Collections::Vector<unsigned int>^ idsInPlay;
        int dimension;
        Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> solidColorBrush;
        Microsoft::WRL::ComPtr<ID2D1BitmapRenderTarget> renderTarget;
        Microsoft::WRL::ComPtr<ID2D1StrokeStyle> strokeStyle;

    public:
        MainPage();

    protected:
        virtual void OnPointerPressed(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args) override;
        virtual void OnPointerMoved(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args) override;
        virtual void OnPointerReleased(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args) override;
        virtual void OnPointerCaptureLost(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args) override;

    private:
        void OnCompositionTargetRendering(Platform::Object^ sender, Platform::Object^ args); 
        void DrawLine(Windows::Foundation::Point point1, Windows::Foundation::Point point2, float thickness);
        void OnClearButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
    };
}
