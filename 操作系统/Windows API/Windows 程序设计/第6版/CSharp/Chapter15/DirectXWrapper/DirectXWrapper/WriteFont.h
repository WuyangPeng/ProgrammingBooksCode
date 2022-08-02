#pragma once

#include "WriteFontMetrics.h"

namespace DirectXWrapper
{
    public ref class WriteFont sealed
    {
    private:
        Microsoft::WRL::ComPtr<IDWriteFont> pWriteFont;

    internal:
        WriteFont(Microsoft::WRL::ComPtr<IDWriteFont> pWriteFont);

    public:
        bool HasCharacter(UINT32 unicodeValue);
        bool IsSymbolFont();
        WriteFontMetrics GetMetrics();
    };
}
