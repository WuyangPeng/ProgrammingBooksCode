//
// RulerContainer.xaml.h
// Declaration of the RulerContainer class
//

#pragma once

#include "pch.h"

namespace XamlCruncher
{
    public ref class TabbableTextBox sealed : Windows::UI::Xaml::Controls::TextBox
    {
    private:
        static Windows::UI::Xaml::DependencyProperty^ tabSpacesProperty;

    public:
        TabbableTextBox();

        static property Windows::UI::Xaml::DependencyProperty^ TabSpacesProperty
        {
            Windows::UI::Xaml::DependencyProperty^ get();
        }

        property int TabSpaces
        {
            void set(int);
            int get();
        }

        property bool IsModified;

        void GetPositionFromIndex(unsigned int index, int* line, int* col);

    private:
        void OnTabKeyDown(Platform::Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ args);
    };
}
