#include "pch.h"
#include "WriteFontCollection.h"
#include "WriteFontFamily.h"

using namespace DirectXWrapper;
using namespace Platform;
using namespace Microsoft::WRL;

WriteFontCollection::WriteFontCollection(ComPtr<IDWriteFontCollection> pFontCollection)
{
    this->pFontCollection = pFontCollection;
}

bool WriteFontCollection::FindFamilyName(String^ familyName, int * index)
{
    uint32 familyIndex;
    BOOL exists;
    HRESULT hr = this->pFontCollection->FindFamilyName(familyName->Data(), &familyIndex, &exists);

    if (!SUCCEEDED(hr))
        throw ref new COMException(hr);

    *index = familyIndex;
 
    return exists != 0;
}

int WriteFontCollection::GetFontFamilyCount()
{
    return pFontCollection->GetFontFamilyCount();
}

WriteFontFamily^ WriteFontCollection::GetFontFamily(int index)
{
    ComPtr<IDWriteFontFamily> pfontFamily;

    HRESULT hr = pFontCollection->GetFontFamily(index, &pfontFamily);

    if (!SUCCEEDED(hr))
        throw ref new COMException(hr);

    return ref new WriteFontFamily(pfontFamily);
}


