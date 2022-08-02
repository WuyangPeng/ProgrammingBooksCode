#include "pch.h"
#include "BooleanToVisibilityConverter.h"

using namespace YoungGoodmanBrown;

using namespace Platform;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Interop;

Object^ BooleanToVisibilityConverter::Convert(Object^ value, TypeName targetType, 
                                              Object^ parameter, String^ langauge)
{
    return (bool)value ? Visibility:: Visible : Visibility::Collapsed;
}

Object^ BooleanToVisibilityConverter::ConvertBack(Object^ value, TypeName targetType, 
                                                  Object^ parameter, String^ language)
{
    return value;
}