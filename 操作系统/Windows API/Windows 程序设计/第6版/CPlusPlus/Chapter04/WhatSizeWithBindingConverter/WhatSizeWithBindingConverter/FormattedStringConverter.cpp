#include "pch.h"            // includes sstream!
#include "FormattedStringConverter.h"

using namespace WhatSizeWithBindingConverter;

using namespace std;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Interop;

Object^ FormattedStringConverter::Convert(Object^ value, TypeName targetType, Object^ parameter, String^)
{
    if (targetType.Name == "String" && parameter != nullptr)
    {
        int decimals = _wtoi(dynamic_cast<String^>(parameter)->Data());
        wostringstream strStream;
        strStream.imbue(locale(""));
        strStream.precision(decimals);
        strStream << (double)value;
        return ref new String(strStream.str().c_str());
    }
    return value;
}

Object^ FormattedStringConverter::ConvertBack(Object^ value, TypeName targetType, Object^ parameter, String^)
{
    return value;
}
