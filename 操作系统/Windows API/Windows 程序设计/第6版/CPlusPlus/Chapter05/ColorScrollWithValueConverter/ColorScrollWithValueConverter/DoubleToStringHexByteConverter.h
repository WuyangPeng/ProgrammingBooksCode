#pragma once

#include "pch.h"

namespace ColorScrollWithValueConverter
{
    public ref class DoubleToStringHexByteConverter sealed : Windows::UI::Xaml::Data::IValueConverter
    {
    public:
        virtual Object^ Convert(Object^ value, Windows::UI::Xaml::Interop::TypeName targetType, Object^ parameter, Platform::String^ language);
        virtual Object^ ConvertBack(Object^ value, Windows::UI::Xaml::Interop::TypeName targetType, Object^ parameter, Platform::String^ language);
    };
}
