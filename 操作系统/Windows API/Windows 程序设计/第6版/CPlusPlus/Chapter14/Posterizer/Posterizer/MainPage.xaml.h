//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace Posterizer
{
    public ref class MainPage sealed
    {
    private:
        Windows::UI::Xaml::Media::Imaging::WriteableBitmap^ bitmap;

        Platform::Array<byte>^ srcPixels;
        Platform::Array<byte>^ dstPixels;
        byte masks[3]; 


    public:
        MainPage();

    private:
        void OnLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);

        void OnOpenAppBarButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnSaveAsAppBarButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);

        void OnRadioButtonChecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnCheckBoxChecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void UpdateBitmap();
        byte * GetPixelPointer(Windows::UI::Xaml::Media::Imaging::WriteableBitmap^ bitmap);
    };
}
