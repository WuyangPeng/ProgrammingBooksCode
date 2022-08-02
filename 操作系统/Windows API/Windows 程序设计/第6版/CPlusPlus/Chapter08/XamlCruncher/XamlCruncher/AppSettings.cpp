#include "pch.h"
#include "AppSettings.h"

using namespace XamlCruncher;

using namespace Platform;
using namespace Windows::Storage;
using namespace Windows::UI;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Media;

AppSettings::AppSettings()
{
    // Application settings initial values
    editOrientation = XamlCruncher::EditOrientation::Left;
    orientation = Windows::UI::Xaml::Controls::Orientation::Horizontal;
    swapEditAndDisplay = false;
    autoParsing = false;
    showRuler = false;
    showGridLines = false;
    fontSize = 18;
    tabSpaces = 4;

    ApplicationDataContainer^ appData = ApplicationData::Current->LocalSettings;

    if (appData->Values->HasKey("EditOrientation"))
        this->EditOrientation = XamlCruncher::EditOrientation((int)appData->Values->Lookup("EditOrientation"));

    if (appData->Values->HasKey("AutoParsing"))
        this->AutoParsing = (bool)appData->Values->Lookup("AutoParsing");

    if (appData->Values->HasKey("ShowRuler"))
        this->ShowRuler = (bool)appData->Values->Lookup("ShowRuler");

    if (appData->Values->HasKey("ShowGridLines"))
        this->ShowGridLines = (bool)appData->Values->Lookup("ShowGridLines");

    if (appData->Values->HasKey("FontSize"))
        this->FontSize = (double)appData->Values->Lookup("FontSize");

    if (appData->Values->HasKey("TabSpaces"))
        this->TabSpaces = (int)appData->Values->Lookup("TabSpaces");
}

void AppSettings::Save()
{
    ApplicationDataContainer^ appData = ApplicationData::Current->LocalSettings;
    appData->Values->Clear();
    appData->Values->Insert("EditOrientation", (int)this->EditOrientation);
    appData->Values->Insert("AutoParsing", (bool)this->AutoParsing);
    appData->Values->Insert("ShowRuler", this->ShowRuler);
    appData->Values->Insert("ShowGridLines", this->ShowGridLines);
    appData->Values->Insert("FontSize", this->FontSize);
    appData->Values->Insert("TabSpaces", this->TabSpaces);
}

void AppSettings::EditOrientation::set(XamlCruncher::EditOrientation value)
{
    if (editOrientation != value)
    {
        editOrientation = value;
        OnPropertyChanged("EditOrientation");

        switch (editOrientation)
        {
        case XamlCruncher::EditOrientation::Left:
            SetOrientation(Windows::UI::Xaml::Controls::Orientation::Horizontal);
            SetSwapEditAndDisplay(false);
            break;

        case XamlCruncher::EditOrientation::Top:
            SetOrientation(Windows::UI::Xaml::Controls::Orientation::Vertical);
            SetSwapEditAndDisplay(false);
            break;

        case XamlCruncher::EditOrientation::Right:
            SetOrientation(Windows::UI::Xaml::Controls::Orientation::Horizontal);
            SetSwapEditAndDisplay(true);
            break;

        case XamlCruncher::EditOrientation::Bottom:
            SetOrientation(Windows::UI::Xaml::Controls::Orientation::Vertical);
            SetSwapEditAndDisplay(true);
            break;
        }
    }
}

EditOrientation AppSettings::EditOrientation::get()
{
    return editOrientation;
}

void AppSettings::SetOrientation(Windows::UI::Xaml::Controls::Orientation value)
{
    if (orientation != value)
    {
        orientation = value;
        OnPropertyChanged("Orientation");
    }
}

Windows::UI::Xaml::Controls::Orientation AppSettings::Orientation::get()
{
    return orientation;
}

void AppSettings::SetSwapEditAndDisplay(bool value)
{
    if (swapEditAndDisplay != value)
    {
        swapEditAndDisplay = value;
        OnPropertyChanged("SwapEditAndDisplay");
    }
}

bool AppSettings::SwapEditAndDisplay::get()
{
    return swapEditAndDisplay;
}

void AppSettings::AutoParsing::set(bool value)
{
    if (autoParsing != value)
    {
        autoParsing = value;
        OnPropertyChanged("AutoParsing");
    }
}

bool AppSettings::AutoParsing::get()
{
    return autoParsing;
}

void AppSettings::ShowRuler::set(bool value)
{
    if (showRuler != value)
    {
        showRuler = value;
        OnPropertyChanged("ShowRuler");
    }
}

bool AppSettings::ShowRuler::get()
{
    return showRuler;
}

void AppSettings::ShowGridLines::set(bool value)
{
    if (showGridLines != value)
    {
        showGridLines = value;
        OnPropertyChanged("ShowGridLines");
    }
}

bool AppSettings::ShowGridLines::get()
{
    return showGridLines;
}

void AppSettings::FontSize::set(double value)
{
    if (fontSize != value)
    {
        fontSize = value;
        OnPropertyChanged("FontSize");
    }
}

double AppSettings::FontSize::get()
{
    return fontSize;
}

void AppSettings::TabSpaces::set(int value)
{
    if (tabSpaces != value)
    {
        tabSpaces = value;
        OnPropertyChanged("TabSpaces");
    }
}

int AppSettings::TabSpaces::get()
{
    return tabSpaces;
}

void AppSettings::OnPropertyChanged(String^ propertyName)
{
    PropertyChanged(this, ref new PropertyChangedEventArgs(propertyName));
}
