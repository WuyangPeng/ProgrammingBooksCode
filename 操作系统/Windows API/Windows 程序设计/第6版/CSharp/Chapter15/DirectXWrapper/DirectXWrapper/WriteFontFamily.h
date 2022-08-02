#pragma once

#include "WriteLocalizedStrings.h"
#include "WriteFont.h"

namespace DirectXWrapper
{
    public ref class WriteFontFamily sealed
    {
    private:
        Microsoft::WRL::ComPtr<IDWriteFontFamily> pFontFamily;

    internal:
        WriteFontFamily(Microsoft::WRL::ComPtr<IDWriteFontFamily> pFontFamily);

    public:
        WriteLocalizedStrings^ GetFamilyNames();
        WriteFont^ GetFirstMatchingFont(Windows::UI::Text::FontWeight fontWeight,
                                        Windows::UI::Text::FontStretch fontStretch, 
                                        Windows::UI::Text::FontStyle fontStyle);
    };
}
