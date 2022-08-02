#pragma once

namespace ClockRack
{
    [Windows::UI::Xaml::Data::BindableAttribute]
    public ref class ColorItem sealed
    {
    public:
        property Windows::UI::Color ColorValue;
        property Platform::String^ ColorName;
    };
}
