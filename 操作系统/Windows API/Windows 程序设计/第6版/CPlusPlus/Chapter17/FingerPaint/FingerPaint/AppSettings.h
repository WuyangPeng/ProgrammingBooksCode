#pragma once

#include "pch.h"

namespace FingerPaint
{
    [Windows::UI::Xaml::Data::Bindable]
    public ref class AppSettings sealed : Windows::UI::Xaml::Data::INotifyPropertyChanged
    {
    private:
        Platform::String^ loadedFilePath;
        Platform::String^ loadedFilename;
        bool isImageModified;
        Windows::UI::Color color;
        float thickness;

    public:
        AppSettings();

        virtual event Windows::UI::Xaml::Data::PropertyChangedEventHandler^ PropertyChanged;

        void Save();

        property Platform::String^ LoadedFilePath
        {
            void set(Platform::String^ value);
            Platform::String^ get() { return loadedFilePath; }
        }

        property Platform::String^ LoadedFilename
        {
            void set(Platform::String^ value); 
            Platform::String^ get() { return loadedFilename; }
        }

        property bool IsImageModified
        {
            void set(bool value);
            bool get() { return isImageModified; }
        }

        property float Thickness
        {
            void set(float value);
            float get() { return thickness; }
        }

        property Windows::UI::Color Color
        {
            void set(Windows::UI::Color value);
            Windows::UI::Color get() { return color; };
        }

    protected:
        void OnPropertyChanged(Platform::String^ propertyName);
    };
}
