#include "pch.h"
#include "WriteFont.h"

using namespace DirectXWrapper;
using namespace Platform;
using namespace Microsoft::WRL;

WriteFont::WriteFont(ComPtr<IDWriteFont> pWriteFont)
{
    this->pWriteFont = pWriteFont;
}

WriteFontMetrics WriteFont::GetMetrics()
{
    DWRITE_FONT_METRICS fontMetrics;
    this->pWriteFont->GetMetrics(&fontMetrics);

    WriteFontMetrics writeFontMetrics = 
    {
        fontMetrics.designUnitsPerEm, 
        fontMetrics.ascent,
        fontMetrics.descent,
        fontMetrics.lineGap,
        fontMetrics.capHeight,
        fontMetrics.xHeight,
        fontMetrics.underlinePosition,
        fontMetrics.underlineThickness,
        fontMetrics.strikethroughPosition,
        fontMetrics.strikethroughThickness
    };

    return writeFontMetrics;
}

bool WriteFont::HasCharacter(UINT32 unicodeValue)
{
    BOOL exists = 0;
    HRESULT hr = this->pWriteFont->HasCharacter(unicodeValue, &exists);

    if (!SUCCEEDED(hr))
        throw ref new COMException(hr);

    return exists != 0;
}

bool WriteFont::IsSymbolFont()
{
    return this->pWriteFont->IsSymbolFont() != 0;
}
