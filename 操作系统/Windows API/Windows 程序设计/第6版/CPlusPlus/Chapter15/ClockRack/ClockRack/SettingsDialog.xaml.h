//
// SettingsDialog.xaml.h
// Declaration of the SettingsDialog class
//

#pragma once

#include "SettingsDialog.g.h"
#include "TimeZoneManager.h"
#include "TimeZoneClockViewModel.h"
#include "TimeZoneDisplayInfo.h"
#include "ColorItem.h"

namespace ClockRack
{
    public ref class SettingsDialog sealed
    {
    public:
        SettingsDialog(TimeZoneManager^ timeZoneManager);

    private:
        void OnLocationTextBoxTextChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ args);
    };
}
