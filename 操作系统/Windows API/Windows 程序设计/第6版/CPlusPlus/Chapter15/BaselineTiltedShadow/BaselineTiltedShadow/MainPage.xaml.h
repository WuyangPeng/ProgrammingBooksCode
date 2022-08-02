//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace BaselineTiltedShadow
{
    public ref class MainPage sealed
    {
    private:
        Microsoft::WRL::ComPtr<IDWriteFactory> pWriteFactory;
        Microsoft::WRL::ComPtr<IDWriteFontCollection> pWriteFontCollection;

    public:
        MainPage();

    private:
        void OnListBoxSelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ args);
    };
}
