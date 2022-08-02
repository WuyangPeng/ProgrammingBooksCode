#pragma once

#include "WriteFontFamily.h"

namespace DirectXWrapper
{
    public ref class WriteFontCollection sealed
    {
    private:
        Microsoft::WRL::ComPtr<IDWriteFontCollection> pFontCollection;

    internal:
        WriteFontCollection(Microsoft::WRL::ComPtr<IDWriteFontCollection> pFontCollection);

    public:
        bool FindFamilyName(Platform::String^ familyName, int * index);
        int GetFontFamilyCount();
        WriteFontFamily^ GetFontFamily(int index);
    };
}
