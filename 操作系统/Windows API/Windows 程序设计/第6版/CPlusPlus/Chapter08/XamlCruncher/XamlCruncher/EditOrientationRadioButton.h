#pragma once

#include "pch.h"
#include "AppSettings.h"

namespace XamlCruncher
{
    public ref class EditOrientationRadioButton sealed : Windows::UI::Xaml::Controls::RadioButton
    {
    public:
        EditOrientationRadioButton() {}
        property XamlCruncher::EditOrientation EditOrientationTag;  
    };
}
