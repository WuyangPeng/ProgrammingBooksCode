#pragma once

namespace DirectXWrapper
{
    public value struct WriteFontMetrics
    {
        UINT16 DesignUnitsPerEm;
        UINT16 Ascent;
        UINT16 Descent;
        INT16  LineGap;
        UINT16 CapHeight;
        UINT16 XHeight;
        INT16  UnderlinePosition;
        UINT16 UnderlineThickness;
        INT16  StrikethroughPosition;
        UINT16 StrikethroughThickness;
    };
}
