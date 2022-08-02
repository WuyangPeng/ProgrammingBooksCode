//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace WhatRes
{
    public ref class MainPage sealed
    {
    public:
        MainPage();

    private:
        void OnMainPageSizeChanged(Platform::Object^ sender, Windows::UI::Xaml::SizeChangedEventArgs^ args);
        void OnLogicalDpiChanged(Platform::Object^ sender);
        void UpdateDisplay();
    };
}
