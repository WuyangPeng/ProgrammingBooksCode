//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace TapToFlip
{
    public ref class MainPage sealed
    {
    private:
        Windows::UI::Xaml::Media::Animation::Storyboard^ flipStoryboard, ^ flipBackStoryboard;
        bool flipped;

    public:
        MainPage();

    private:
        void OnGridTapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ args);
    };
}
