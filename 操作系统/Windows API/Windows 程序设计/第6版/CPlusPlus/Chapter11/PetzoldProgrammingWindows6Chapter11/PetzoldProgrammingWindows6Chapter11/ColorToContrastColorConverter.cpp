#include "pch.h"
#include "ColorToContrastColorConverter.h"

using namespace PetzoldProgrammingWindows6Chapter11;

using namespace Platform;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Interop;

Object^ ColorToContrastColorConverter::Convert(Object^ value, TypeName targetType, 
                                               Object^ parameter, String^ langauge)
{
    Color clr = (Color)value;
    double grayShade = 0.3 * clr.R + 0.59 * clr.G + 0.11 * clr.B;
    return grayShade > 128 ? Colors::Black : Colors::White;
}

Object^ ColorToContrastColorConverter::ConvertBack(Object^ value, TypeName targetType, 
                                                   Object^ parameter, String^ language)
{
    return value;
}