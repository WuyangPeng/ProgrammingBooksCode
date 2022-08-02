//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace EnumerateFonts;

using namespace Microsoft::WRL;
using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

MainPage::MainPage()
{
    InitializeComponent();

    ComPtr<IDWriteFactory> pWriteFactory;
    HRESULT hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
                                     __uuidof(IDWriteFactory),
                                     &pWriteFactory);

    if (!SUCCEEDED(hr))
    {
        OutputDebugString(L"DWriteCreateFactory fail");
        return;
    }

    ComPtr<IDWriteFontCollection> pWriteFontCollection;
    hr = pWriteFactory->GetSystemFontCollection(&pWriteFontCollection, true);

    if (!SUCCEEDED(hr))
    {
        OutputDebugString(L"GetSystemFontCollection fail");
        return;
    }

    unsigned int count = pWriteFontCollection->GetFontFamilyCount();
    Vector<String^>^ fonts = ref new Vector<String^>();

    for (unsigned int i = 0; i < count; i++)
    {
        ComPtr<IDWriteFontFamily> pWriteFontFamily;
        hr = pWriteFontCollection->GetFontFamily(i, &pWriteFontFamily);

        if (!SUCCEEDED(hr))
        {
            OutputDebugString(L"GetFontFamily fail");
            return;
        }

        ComPtr<IDWriteLocalizedStrings> pWriteFamilyNames;
        hr = pWriteFontFamily->GetFamilyNames(&pWriteFamilyNames);

        if (!SUCCEEDED(hr))
        {
            OutputDebugString(L"GetFamilyNames fail");
            return;
        }

        unsigned int index = 0;
        BOOL exists;

        hr = pWriteFamilyNames->FindLocaleName(L"en-us", &index, &exists);

        if (!SUCCEEDED(hr))
        {
            OutputDebugString(L"FindLocaleName fail");
            return;
        }

        if (exists)
        {
            unsigned int length = 0;
            hr = pWriteFamilyNames->GetStringLength(index, &length);

            if (!SUCCEEDED(hr))
            {
                OutputDebugString(L"GetStringLength fail");
                return;
            }

            wchar_t* str = new (std::nothrow) wchar_t[length + 1];

            if (str == nullptr)
            {
                OutputDebugString(L"Memory allocation fail");
                return;
            }

            hr = pWriteFamilyNames->GetString(index, str, length + 1);

            if (!SUCCEEDED(hr))
            {
                OutputDebugString(L"GetString fail");
                return;
            }

            String^ string = ref new String(str);
            delete[] str;
            fonts->Append(string);
        }
    }

    lstbox->ItemsSource = fonts;
}

