//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace NonAffineStretch
{
    public ref class MainPage sealed
    {
    private:
        Windows::Foundation::Rect imageRect;

    public:
        MainPage();

    private:
        void OnThumbDragDelta(Platform::Object^ sender, Windows::UI::Xaml::Controls::Primitives::DragDeltaEventArgs^ args);
        void CalculateNewTransform();
        static Windows::UI::Xaml::Media::Media3D::Matrix3D CalculateNewTransform(Windows::Foundation::Rect rect,
                                                                                 Windows::Foundation::Point ptUL,
                                                                                 Windows::Foundation::Point ptUR,
                                                                                 Windows::Foundation::Point ptLL,
                                                                                 Windows::Foundation::Point ptLR);
    };
}
