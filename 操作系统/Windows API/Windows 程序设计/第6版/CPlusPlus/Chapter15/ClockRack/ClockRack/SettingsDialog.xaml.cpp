//
// SettingsDialog.xaml.cpp
// Implementation of the SettingsDialog class
//

#include "pch.h"
#include "SettingsDialog.xaml.h"

using namespace ClockRack;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// using namespace ReflectionHelper;

using namespace PetzoldProgrammingWindows6Chapter11;

SettingsDialog::SettingsDialog(TimeZoneManager^ timeZoneManager)
{
    InitializeComponent();

    // Set ItemsSource for time zone ComboBox
    timeZoneComboBox->ItemsSource = timeZoneManager->DisplayInformation;

    // Set ItemsSource for foreground and background ComboBoxes
    foregroundComboBox->ItemsSource = (ref new NamedColor())->All;
    backgroundComboBox->ItemsSource = (ref new NamedColor())->All;
}

void SettingsDialog::OnLocationTextBoxTextChanged(Object^ sender, TextChangedEventArgs^ args)
{
    dynamic_cast<TimeZoneClockViewModel^>(this->DataContext)->Location = dynamic_cast<TextBox^>(sender)->Text;
}