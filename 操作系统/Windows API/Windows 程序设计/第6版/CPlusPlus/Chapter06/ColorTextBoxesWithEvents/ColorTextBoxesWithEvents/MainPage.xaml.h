//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include "RgbViewModel.h"

namespace ColorTextBoxesWithEvents
{
    public ref class MainPage sealed
    {
    public:
        MainPage();

    private:
        ColorTextBoxesWithEvents::RgbViewModel^ rgbViewModel;
        Windows::UI::Xaml::Media::Brush^ textBoxTextBrush;
        Windows::UI::Xaml::Media::Brush^ textBoxErrorBrush;

        void OnRgbViewModelPropertyChanged(Platform::Object^ sender, Windows::UI::Xaml::Data::PropertyChangedEventArgs^ args);
        void OnTextBoxTextChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ args);
        bool Validate(Windows::UI::Xaml::Controls::TextBox^ txtbox, int* value);
    };
}
