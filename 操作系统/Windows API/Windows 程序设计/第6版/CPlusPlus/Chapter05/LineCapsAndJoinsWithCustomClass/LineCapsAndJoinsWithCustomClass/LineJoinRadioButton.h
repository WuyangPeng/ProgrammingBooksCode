#pragma once

#include "pch.h"

namespace LineCapsAndJoinsWithCustomClass
{
    public ref class LineJoinRadioButton sealed : Windows::UI::Xaml::Controls::RadioButton
    {
    public:
        property Windows::UI::Xaml::Media::PenLineJoin LineJoinTag;  
    };
}
