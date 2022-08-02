#pragma once

#include "pch.h"

namespace LineCapsAndJoinsWithCustomClass
{
    public ref class LineCapRadioButton sealed : Windows::UI::Xaml::Controls::RadioButton
    {
    public:
        property Windows::UI::Xaml::Media::PenLineCap LineCapTag;  
    };
}
