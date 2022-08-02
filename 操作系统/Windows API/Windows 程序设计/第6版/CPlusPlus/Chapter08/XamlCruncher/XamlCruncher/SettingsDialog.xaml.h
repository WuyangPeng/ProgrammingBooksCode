//
// SettingsDialog.xaml.h
// Declaration of the SettingsDialog class
//

#pragma once

#include "pch.h"
#include "SettingsDialog.g.h"
#include "EditOrientationRadioButton.h"

namespace XamlCruncher
{
    public ref class SettingsDialog sealed
    {
    public:
        SettingsDialog();

    private:
        void OnLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void OnOrientationRadioButtonChecked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
    };
}
