#pragma once

#include "WriteFontCollection.h"

namespace DirectXWrapper
{
    public ref class WriteFactory sealed
    {
    private:
        Microsoft::WRL::ComPtr<IDWriteFactory> pFactory;

    public:
        WriteFactory();
        WriteFontCollection^ GetSystemFontCollection();
        WriteFontCollection^ GetSystemFontCollection(bool checkForUpdates);
    };
}
