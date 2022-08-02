#pragma once

namespace PetzoldProgrammingWindows6Chapter11
{
    [Windows::Foundation::Metadata::WebHostHidden]
    public ref class ColorToContrastColorConverter sealed : Windows::UI::Xaml::Data::IValueConverter
    {
    public:
        virtual Object^ Convert(Platform::Object^ value, 
                                Windows::UI::Xaml::Interop::TypeName targetType, 
                                Platform::Object^ parameter, 
                                Platform::String^ language);

        virtual Object^ ConvertBack(Platform::Object^ value, 
                                    Windows::UI::Xaml::Interop::TypeName targetType, 
                                    Platform::Object^ parameter, 
                                    Platform::String^ language);
    };
}