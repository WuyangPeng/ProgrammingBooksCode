//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace SimpleContextMenu
{
    public ref class MainPage sealed
    {
    public:
        MainPage();

    private:
        void OnTextBlockRightTapped(Platform::Object^ sender, Windows::UI::Xaml::Input::RightTappedRoutedEventArgs^ args);
        void OnFontSizeChanged(Windows::UI::Popups::IUICommand^ command);
        void OnColorChanged(Windows::UI::Popups::IUICommand^ command);
    };
}
