//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace BaselineTiltedShadow;

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

    HRESULT hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
                                     __uuidof(IDWriteFactory),
                                     &pWriteFactory);

    if (!SUCCEEDED(hr))
    {
        OutputDebugString(L"DWriteCreateFactory fail");
        return;
    }

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

    Loaded += ref new RoutedEventHandler([this] (Object^ sender, RoutedEventArgs^ args)
    {
        lstbox->SelectedIndex = 0;
    });
}

void MainPage::OnListBoxSelectionChanged(Object^ sender, SelectionChangedEventArgs^ args)
{
    String^ fontFamily = dynamic_cast<String^>(dynamic_cast<ListBox^>(sender)->SelectedItem);

    if (fontFamily == nullptr)
        return;

    foregroundTextBlock->FontFamily = ref new Windows::UI::Xaml::Media::FontFamily(fontFamily);
    shadowTextBlock->FontFamily = foregroundTextBlock->FontFamily;

    unsigned int index;
    BOOL exists;
    HRESULT hr = pWriteFontCollection->FindFamilyName(fontFamily->Data(), &index, &exists);

    if (!SUCCEEDED(hr))
    {
        OutputDebugString(L"FindFamilyName fail");
        return;
    }

    ComPtr<IDWriteFontFamily> pWriteFontFamily;
    hr = pWriteFontCollection->GetFontFamily(index, &pWriteFontFamily);
    
    if (!SUCCEEDED(hr))
    {
        OutputDebugString(L"GetFontFamily fail");
        return;
    }
    
    ComPtr<IDWriteFont> pWriteFont;
    hr = pWriteFontFamily->GetFirstMatchingFont(DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_NORMAL,
                                                DWRITE_FONT_STRETCH::DWRITE_FONT_STRETCH_NORMAL, 
                                                DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_NORMAL, 
                                                &pWriteFont);

    if (!SUCCEEDED(hr))
    {
        OutputDebugString(L"GetString fail");
        return;
    }

    DWRITE_FONT_METRICS fontMetrics;
    pWriteFont->GetMetrics(&fontMetrics);

    float fractionAboveBaseline = (float)fontMetrics.ascent / 
                (fontMetrics.ascent + fontMetrics.descent + fontMetrics.lineGap);

    shadowTextBlock->RenderTransformOrigin = Point(0, fractionAboveBaseline);
}
