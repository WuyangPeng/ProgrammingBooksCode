#pragma once

namespace DirectXWrapper
{
    public ref class WriteLocalizedStrings sealed
    {
    private:
        Microsoft::WRL::ComPtr<IDWriteLocalizedStrings> pLocalizedStrings;

    internal:
        WriteLocalizedStrings(Microsoft::WRL::ComPtr<IDWriteLocalizedStrings> pLocalizedStrings);

    public:
        int GetCount();
        Platform::String^ GetLocaleName(int index);
        Platform::String^ GetString(int index);
        bool FindLocaleName(Platform::String^ localeName, int * index);
    };
}
