#include "pch.h"
#include "AppSettings.h"

using namespace FingerPaint;

using namespace Platform;
using namespace Windows::Foundation::Collections;
using namespace Windows::Storage;
using namespace Windows::UI;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Media;

AppSettings::AppSettings()
{
    IPropertySet^ props = ApplicationData::Current->LocalSettings->Values;
    this->LoadedFilePath = props->HasKey("LoadedFilePath") ? dynamic_cast<String^>(props->Lookup("LoadedFilePath")) : nullptr;
    this->LoadedFilename = props->HasKey("LoadedFilename") ? dynamic_cast<String^>(props->Lookup("LoadedFilename")) : nullptr;
    this->isImageModified = props->HasKey("IsImageModified") ? (bool)props->Lookup("IsImageModified") : false;
    this->Thickness = props->HasKey("Thickness") ? (float)props->Lookup("Thickness") : 16;

    if (props->HasKey("Color.Red") && props->HasKey("Color.Green") && props->HasKey("Color.Blue"))
    {
        this->Color = ColorHelper::FromArgb(255,
                                            (byte)props->Lookup("Color.Red"),
                                            (byte)props->Lookup("Color.Green"),
                                            (byte)props->Lookup("Color.Blue"));    
    }
    else
    {
        this->Color = Colors::Blue;
    }
}

void AppSettings::Save()
{
    IPropertySet^ props = ApplicationData::Current->LocalSettings->Values;
    props->Clear();
    props->Insert("LoadedFilePath", this->LoadedFilePath);
    props->Insert("LoadedFilename", this->LoadedFilename);
    props->Insert("IsImageModified", this->IsImageModified);
    props->Insert("Thickness", this->Thickness);
    props->Insert("Color.Red", this->Color.R);
    props->Insert("Color.Green", this->Color.G);
    props->Insert("Color.Blue", this->Color.B);
}

void AppSettings::LoadedFilePath::set(String^ value)
{
    if (!loadedFilePath->Equals(value))
    {
        loadedFilePath = value;
        OnPropertyChanged("LoadedFilePath");
    }
}

void AppSettings::LoadedFilename::set(String^ value)
{
    if (!loadedFilename->Equals(value))
    {
        loadedFilename = value;
        OnPropertyChanged("LoadedFilename");
    }
}

void AppSettings::IsImageModified::set(bool value)
{
    if (isImageModified != value)
    {
        isImageModified = value;
        OnPropertyChanged("IsImageModified");
    }
}

void AppSettings::Thickness::set(float value)
{
    if (thickness != value)
    {
        thickness = value;
        OnPropertyChanged("Thickness");
    }
}

void AppSettings::Color::set(Windows::UI::Color value)
{
    if (!color.Equals(value))
    {
        color = value;
        OnPropertyChanged("Color");
    }
}

void AppSettings::OnPropertyChanged(String^ propertyName)
{
    PropertyChanged(this, ref new PropertyChangedEventArgs(propertyName));
}
