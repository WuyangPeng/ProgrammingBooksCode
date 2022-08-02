//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace InkEraseSelect
{
    public ref class MainPage sealed
    {
    private:
        Windows::UI::Input::Inking::InkManager^ inkManager;
        Windows::UI::Input::Inking::InkDrawingAttributes^ inkDrawingAttributes;
        bool hasPen;
        Platform::Collections::Map<unsigned int, Windows::Foundation::Point>^ pointerDictionary;
        Windows::UI::Xaml::Media::Brush^ selectionBrush;

    public:
        MainPage();

    protected:
        virtual void OnPointerPressed(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args) override;
        virtual void OnPointerMoved(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args) override;
        virtual void OnPointerReleased(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args) override;
        virtual void OnPointerCaptureLost(Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args) override;

        void RenderAll();
        void RenderStroke(Windows::UI::Input::Inking::InkStroke^ inkStroke);
        static void RenderBeziers(Windows::UI::Xaml::Controls::Panel^ panel, 
                                  Windows::UI::Input::Inking::InkStroke^ inkStroke, 
                                  Windows::UI::Color color, 
                                  double penSize);

        void OnAppBarOpened(Platform::Object^ sender, Platform::Object^ args);
        void OnCopyAppBarButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnCutAppBarButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnPasteAppBarButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnDeleteAppBarButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
    };
}
