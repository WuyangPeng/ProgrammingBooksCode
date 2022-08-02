#pragma once

#include "pch.h"

namespace ManipulationTracker
{
    public ref class ManipulationModeCheckBox sealed : Windows::UI::Xaml::Controls::CheckBox
    {
    public:
        ManipulationModeCheckBox() {}

        property Windows::UI::Xaml::Input::ManipulationModes ManipulationModes;  
    };
}
