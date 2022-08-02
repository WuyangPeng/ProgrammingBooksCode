#include "pch.h"
#include "DoubleToStringHexByteConverter.h"

using namespace SegoeSymbols;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Interop;

Object^ DoubleToStringHexByteConverter::Convert(Object^ value, TypeName targetType, Object^ parameter, String^)
{
    wchar_t result[6];
    swprintf(result, sizeof(result) / sizeof(result[0]), L"%02X__", (int)(double)value);
    return ref new String(result);
}

Object^ DoubleToStringHexByteConverter::ConvertBack(Object^ value, TypeName targetType, Object^ parameter, String^)
{
    return value;
}
