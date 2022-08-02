#pragma once

#include "ClockBase.h"

namespace ClockButton
{
    [Windows::UI::Xaml::Data::BindableAttribute]
    public ref class Clock sealed : ClockBase
    {
    public:
        Clock() {}
    };
}
