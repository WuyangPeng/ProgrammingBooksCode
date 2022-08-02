//
// ColorItem.xaml.h
// Declaration of the ColorItem class
//

#pragma once

#include "pch.h"
#include "ColorItem.g.h"

namespace PetzoldWindows8Controls
{
    public ref class ColorItem sealed
    {
    public:
        ColorItem::ColorItem(Platform::String^ name, Windows::UI::Color clr);
    };
}
