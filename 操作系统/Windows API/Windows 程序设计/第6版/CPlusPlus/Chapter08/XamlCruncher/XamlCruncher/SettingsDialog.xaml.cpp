//
// SettingsDialog.xaml.cpp
// Implementation of the SettingsDialog class
//

#include "pch.h"
#include "SettingsDialog.xaml.h"
#include "AppSettings.h"

using namespace XamlCruncher;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

SettingsDialog::SettingsDialog()
{
    InitializeComponent();
    Loaded += ref new RoutedEventHandler(this, &SettingsDialog::OnLoaded);
}

void SettingsDialog::OnLoaded(Object^ sender, RoutedEventArgs^ args)
{
    AppSettings^ appSettings = dynamic_cast<AppSettings^>(this->DataContext);

    if (appSettings != nullptr)
    {
        for (unsigned int index = 0; index < this->orientationRadioButtonGrid->Children->Size; index++)
        {
            EditOrientationRadioButton^ radioButton = dynamic_cast<EditOrientationRadioButton^>(orientationRadioButtonGrid->Children->GetAt(index));
            radioButton->IsChecked = appSettings->EditOrientation == radioButton->EditOrientationTag;
        }
    }
}

void SettingsDialog::OnOrientationRadioButtonChecked(Object^ sender, RoutedEventArgs^ args)
{
    AppSettings^ appSettings = dynamic_cast<AppSettings^>(this->DataContext);
    EditOrientationRadioButton^ radioButton = dynamic_cast<EditOrientationRadioButton^>(sender);

    if (appSettings != nullptr)
        appSettings->EditOrientation = radioButton->EditOrientationTag;
}

