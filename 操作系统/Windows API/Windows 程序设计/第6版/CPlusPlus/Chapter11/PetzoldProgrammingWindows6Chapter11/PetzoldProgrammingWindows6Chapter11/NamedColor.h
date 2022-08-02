#pragma once

namespace PetzoldProgrammingWindows6Chapter11
{
    [Windows::UI::Xaml::Data::Bindable]
    public ref class NamedColor sealed
    {
    private:
        static Windows::Foundation::Collections::IIterable<NamedColor^>^ all;
        Platform::String^ name;
        Windows::UI::Color color;

    public:
        NamedColor() {}

        // Making the All property static doesn't work in ColorItemsSourceWithBinding XAML binding

        property Windows::Foundation::Collections::IIterable<NamedColor^>^ All
        {
            Windows::Foundation::Collections::IIterable<NamedColor^>^ get();
        }

        property Platform::String^ Name
        {
            Platform::String^ get() { return name; }
        }

        property Windows::UI::Color Color
        {
            Windows::UI::Color get() { return color; }
        }

        // In the C++ version, additional properties are required because
        // A, R, G, and B and fields in the C++ color structure and don't
        // work with the bindings.

        property unsigned char A
        {
            unsigned char get() { return color.A; }
        }

        property unsigned char R
        {
            unsigned char get() { return color.R; }
        }

        property unsigned char G
        {
            unsigned char get() { return color.G; }
        }

        property unsigned char B
        {
            unsigned char get() { return color.B; }
        }
    };
}