#include "pch.h"
#include "WriteFontFamily.h"

using namespace DirectXWrapper;
using namespace Platform;
using namespace Microsoft::WRL;
using namespace Windows::UI::Text;

WriteFontFamily::WriteFontFamily(ComPtr<IDWriteFontFamily> pFontFamily)
{
    this->pFontFamily = pFontFamily;
}

WriteLocalizedStrings^ WriteFontFamily::GetFamilyNames()
{
    ComPtr<IDWriteLocalizedStrings> pFamilyNames;

    HRESULT hr = pFontFamily->GetFamilyNames(&pFamilyNames);

    if (!SUCCEEDED(hr))
        throw ref new COMException(hr);

    return ref new WriteLocalizedStrings(pFamilyNames);
}

WriteFont^ WriteFontFamily::GetFirstMatchingFont(FontWeight fontWeight, 
                                                 FontStretch fontStretch, 
                                                 FontStyle fontStyle)
{
    // Convert font weight from Windows Runtime to DirectX
    DWRITE_FONT_WEIGHT writeFontWeight = DWRITE_FONT_WEIGHT_NORMAL;

    if (fontWeight.Equals(FontWeights::Black))
        writeFontWeight = DWRITE_FONT_WEIGHT_BLACK;

    else if (fontWeight.Equals(FontWeights::Bold))
        writeFontWeight = DWRITE_FONT_WEIGHT_BOLD;

    else if (fontWeight.Equals(FontWeights::ExtraBlack))
        writeFontWeight = DWRITE_FONT_WEIGHT_EXTRA_BLACK;

    else if (fontWeight.Equals(FontWeights::ExtraBold))
        writeFontWeight = DWRITE_FONT_WEIGHT_EXTRA_BOLD;

    else if (fontWeight.Equals(FontWeights::ExtraLight))
        writeFontWeight = DWRITE_FONT_WEIGHT_EXTRA_LIGHT;

    else if (fontWeight.Equals(FontWeights::Light))
        writeFontWeight = DWRITE_FONT_WEIGHT_LIGHT;

    else if (fontWeight.Equals(FontWeights::Medium))
        writeFontWeight = DWRITE_FONT_WEIGHT_MEDIUM;

    else if (fontWeight.Equals(FontWeights::Normal))
        writeFontWeight = DWRITE_FONT_WEIGHT_NORMAL;

    else if (fontWeight.Equals(FontWeights::SemiBold))
        writeFontWeight = DWRITE_FONT_WEIGHT_SEMI_BOLD;

    else if (fontWeight.Equals(FontWeights::SemiLight))
        writeFontWeight = DWRITE_FONT_WEIGHT_SEMI_LIGHT;

    else if (fontWeight.Equals(FontWeights::Thin))
        writeFontWeight = DWRITE_FONT_WEIGHT_THIN;

    // Convert font stretch from Windows Runtime to DirectX
    DWRITE_FONT_STRETCH writeFontStretch = (DWRITE_FONT_STRETCH)fontStretch;

    // Convert font style from Windows Runtime to DirectX
    DWRITE_FONT_STYLE writeFontStyle = (DWRITE_FONT_STYLE)fontStyle;

    ComPtr<IDWriteFont> pWriteFont = nullptr;
    HRESULT hr = pFontFamily->GetFirstMatchingFont(writeFontWeight, 
                                                   writeFontStretch, 
                                                   writeFontStyle, 
                                                   &pWriteFont);
    if (!SUCCEEDED(hr))
        throw ref new COMException(hr);

    return ref new WriteFont(pWriteFont);
}

