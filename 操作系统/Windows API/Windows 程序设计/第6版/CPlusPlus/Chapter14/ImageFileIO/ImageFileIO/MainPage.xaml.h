//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace ImageFileIO
{
    public ref class MainPage sealed
    {
    private:
        double dpiX, dpiY;

    public:
        MainPage();

    private:
        void OnOpenAppBarButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnSaveAsAppBarButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnRotateLeftAppBarButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnRotateRightAppBarButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void Rotate(int (*calculateSourceIndex)(Windows::UI::Xaml::Media::Imaging::BitmapSource^, int, int));
        byte * GetPixelPointer(Windows::UI::Xaml::Media::Imaging::WriteableBitmap^ bitmap);
    };
}
