#pragma once

namespace ClockRack
{
    [Windows::UI::Xaml::Data::BindableAttribute]
    public ref struct TimeZoneDisplayInfo sealed
    {
        property int Bias;
        property Platform::String^ TimeZoneKey;
        property Platform::String^ Display;
    };
}
