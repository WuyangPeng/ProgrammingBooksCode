//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace InkAndErase
{
    public ref class MainPage sealed
    {
    private:
        Windows::UI::Input::Inking::InkManager^ inkManager;
        Windows::UI::Input::Inking::InkDrawingAttributes^ inkDrawingAttributes;
        bool hasPen;
        Platform::Collections::Map<unsigned int, Windows::Foundation::Point>^ pointerDictionary;

    public:
        MainPage();

    protected:
        virtual void OnPointerPressed(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args) override;
        virtual void OnPointerMoved(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args) override;
        virtual void OnPointerReleased(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args) override;
        virtual void OnPointerCaptureLost(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args) override;

        void RenderAll();
        void RenderStroke(Windows::UI::Input::Inking::InkStroke^ inkStroke);
    };
}
