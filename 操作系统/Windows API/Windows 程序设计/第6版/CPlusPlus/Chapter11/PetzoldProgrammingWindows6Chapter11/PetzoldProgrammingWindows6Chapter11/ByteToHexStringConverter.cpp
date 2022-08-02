#include "pch.h"
#include "ByteToHexStringConverter.h"

using namespace PetzoldProgrammingWindows6Chapter11;

using namespace Platform;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Interop;

Object^ ByteToHexStringConverter::Convert(Object^ value, TypeName targetType, 
                                          Object^ parameter, String^ langauge)
{
    wchar_t result[10];
    swprintf(result, 10, L"%02X", (unsigned char)value);
    return ref new String(result);
}

Object^ ByteToHexStringConverter::ConvertBack(Object^ value, TypeName targetType, 
                                              Object^ parameter, String^ language)
{
    return value;
}