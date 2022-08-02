//
// ColorItem.xaml.h
// Declaration of the ColorItem class
//

#pragma once

#include "pch.h"
#include "ColorItem.g.h"

namespace ColorList2
{
    public ref class ColorItem sealed
    {
    public:
        ColorItem(Platform::String^ name, Windows::UI::Color clr);
    };
}
