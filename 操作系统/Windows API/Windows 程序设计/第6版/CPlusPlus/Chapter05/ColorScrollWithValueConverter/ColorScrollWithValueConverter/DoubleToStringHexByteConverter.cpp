#include "pch.h"
#include "DoubleToStringHexByteConverter.h"

using namespace ColorScrollWithValueConverter;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Interop;

Object^ DoubleToStringHexByteConverter::Convert(Object^ value, TypeName targetType, Object^ parameter, String^)
{
    wchar_t result[4];
    swprintf(result, 4, L"%02X", (int)(double)value);
    return ref new String(result);
}

Object^ DoubleToStringHexByteConverter::ConvertBack(Object^ value, TypeName targetType, Object^ parameter, String^)
{
    return value;
}
