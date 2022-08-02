#include "pch.h"
#include "WriteFactory.h"

using namespace DirectXWrapper;
using namespace Platform;
using namespace Microsoft::WRL;

WriteFactory::WriteFactory()
{
    HRESULT hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, 
                                     __uuidof(IDWriteFactory), 
                                     &pFactory);

    if (!SUCCEEDED(hr))
        throw ref new COMException(hr);
}

WriteFontCollection^ WriteFactory::GetSystemFontCollection()
{
    return GetSystemFontCollection(false);
}

WriteFontCollection^ WriteFactory::GetSystemFontCollection(bool checkForUpdates)
{
    ComPtr<IDWriteFontCollection> pFontCollection;

    HRESULT hr = pFactory->GetSystemFontCollection(&pFontCollection, checkForUpdates);

    if (!SUCCEEDED(hr))
        throw ref new COMException(hr);

    return ref new WriteFontCollection(pFontCollection);
}
