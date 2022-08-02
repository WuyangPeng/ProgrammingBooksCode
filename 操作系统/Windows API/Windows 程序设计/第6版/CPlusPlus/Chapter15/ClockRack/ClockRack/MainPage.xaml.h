//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include "TimeZoneManager.h"
#include "SettingsDialog.xaml.h"

namespace ClockRack
{
    public ref class MainPage sealed
    {
    private:
        TimeZoneManager^ timeZoneManager;
        Windows::Foundation::Collections::IPropertySet^ appSettings;
        Windows::Globalization::Calendar^ calendar;

    public:
        MainPage();

    protected:
        void OnRightTapped(Windows::UI::Xaml::Input::RightTappedRoutedEventArgs^ args) override;

    private:
        void OnApplicationSuspending(Platform::Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ args);
        void OnCompositionTargetRendering(Platform::Object^ sender, Platform::Object^ args);
        void RecalculateClockSize();
        void OnAddMenuItem(Windows::UI::Popups::IUICommand^ command);
        void OnEditMenuItem(Windows::UI::Popups::IUICommand^ command);
        void OnDeleteMenuItem(Windows::UI::Popups::IUICommand^ command);
    };
}
