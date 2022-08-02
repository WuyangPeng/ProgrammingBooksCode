//
// AboutBox.xaml.h
// Declaration of the AboutBox class
//

#pragma once

#include "AboutBox.g.h"

namespace FingerPaint
{
    [Windows::Foundation::Metadata::WebHostHidden]
    public ref class AboutBox sealed
    {
    public:
        AboutBox();

    private:
        void OnBackButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^  args);
    };
}
