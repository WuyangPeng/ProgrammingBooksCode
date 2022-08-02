#pragma once

#include "pch.h"
#include "EditOrientation.h"

namespace XamlCruncher
{
    [Windows::UI::Xaml::Data::Bindable]
    public ref class AppSettings sealed : Windows::UI::Xaml::Data::INotifyPropertyChanged
    {
    private:
        XamlCruncher::EditOrientation editOrientation;
        Windows::UI::Xaml::Controls::Orientation orientation;
        bool swapEditAndDisplay;
        bool autoParsing;
        bool showRuler;
        bool showGridLines;
        double fontSize;
        int tabSpaces;

    public:
        AppSettings();

        virtual event Windows::UI::Xaml::Data::PropertyChangedEventHandler^ PropertyChanged;

        void Save();

        property EditOrientation EditOrientation
        {
            void set(XamlCruncher::EditOrientation);
            XamlCruncher::EditOrientation get();
        }

        property Windows::UI::Xaml::Controls::Orientation Orientation
        {
            Windows::UI::Xaml::Controls::Orientation get();
        }

        property bool SwapEditAndDisplay
        {
            bool get();
        }

        property bool AutoParsing
        {
            void set(bool);
            bool get();
        }

        property bool ShowRuler
        {
            void set(bool);
            bool get();
        }

        property bool ShowGridLines
        {
            void set(bool);
            bool get();
        }

        property double FontSize
        {
            void set(double);
            double get();
        }

        property int TabSpaces
        {
            void set(int);
            int get();
        }

    protected:
        void SetOrientation(Windows::UI::Xaml::Controls::Orientation value);
        void SetSwapEditAndDisplay(bool value);
        void OnPropertyChanged(Platform::String^ propertyName);
    };
}
