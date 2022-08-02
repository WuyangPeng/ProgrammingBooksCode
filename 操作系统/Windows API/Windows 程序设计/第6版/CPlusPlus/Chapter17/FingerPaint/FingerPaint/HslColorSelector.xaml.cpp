//
// HslColorSelector.xaml.cpp
// Implementation of the HslColorSelector class
//

#include "pch.h"
#include "HslColorSelector.xaml.h"

using namespace FingerPaint;

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Storage::Streams;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Media::Imaging;
using namespace Windows::UI::Xaml::Navigation;

DependencyProperty^ HslColorSelector::colorProperty = 
    DependencyProperty::Register("Color", 
                                 TypeName(Windows::UI::Color::typeid), 
                                 TypeName(HslColorSelector::typeid), 
                                 ref new PropertyMetadata((Colors::Black), 
                                 ref new PropertyChangedCallback(&HslColorSelector::OnColorChangedStatic)));

HslColorSelector::HslColorSelector()
{
    InitializeComponent();
    doNotSetSliders = false;
    Loaded += ref new RoutedEventHandler(this, &HslColorSelector::OnLoaded);
}

void HslColorSelector::OnLoaded(Object^ sender, RoutedEventArgs^ args)
{
    // Build bitmap for hue/saturation grid
    WriteableBitmap^ bitmap = ref new WriteableBitmap(256, 256);

    // Obtain IBufferByteAccess
    IBuffer^ buffer = bitmap->PixelBuffer;
    ComPtr<IBufferByteAccess> pBufferByteAccess;
    ComPtr<IUnknown> pBuffer((IUnknown*)buffer);
    pBuffer.As(&pBufferByteAccess);

    // Get pointer to pixel bytes
    byte* pixels;
    pBufferByteAccess->Buffer(&pixels);
    int index = 0;

    for (int y = 0; y < 256; y++)
        for (int x = 0; x < 256; x++)
        {
            Windows::UI::Color clr = HslToRgb(byte(x), byte(255 - y), byte(128));
            pixels[index++] = clr.B;
            pixels[index++] = clr.G;
            pixels[index++] = clr.R;
            pixels[index++] = clr.A;
        }

    bitmap->Invalidate();
    hsImage->Source = bitmap;
}

// Event handlers for sliders
void HslColorSelector::OnXYSliderValueChanged(Object^ sender, Point point)
{
    Windows::UI::Color clr = HslToRgb(int(255 * point.X), int(255 * (1 - point.Y)), 128);
    sliderGradientStop->Color = clr;
    SetColorFromSliders();
}

void HslColorSelector::OnSliderValueChanged(Object^ sender, RangeBaseValueChangedEventArgs^ args)
{
    SetColorFromSliders();
}

void HslColorSelector::SetColorFromSliders()
{
    Point point = xySlider->Value;
    double value = slider->Value;

    doNotSetSliders = true;
    this->Color = HslToRgb(int(255 * point.X), int(255 * (1 - point.Y)), int(255 * value / 100));
    doNotSetSliders = false;    
}

void HslColorSelector::OnColorChangedStatic(DependencyObject^ obj, DependencyPropertyChangedEventArgs^ args)
{
    dynamic_cast<HslColorSelector^>(obj)->OnColorChanged((Windows::UI::Color)args->NewValue);
}

void HslColorSelector::OnColorChanged(Windows::UI::Color color)
{
    int h, s, l;
    RgbToHsl(color, &h, &s, &l);

    if (!doNotSetSliders)
    {
        xySlider->Value = Point(h / 255.0f, 1 - s / 255.0f);
        slider->Value = 100.0 * l / 255;
    }

    wchar_t str[32];
    swprintf_s(str, 32, L"RGB = %i, %i, %i", this->Color.R, this->Color.G, this->Color.B);
    txtblk->Text = ref new String(str);

    ColorChanged(this, color);
}

Windows::UI::Color HslColorSelector::HslToRgb(int h, int s, int l)
{
    XMVECTOR hsl = XMVectorSet(h / 255.0f, s / 255.0f, l / 255.0f, 1.0f);
    XMVECTOR rgb = XMColorHSLToRGB(hsl);
    return ColorHelper::FromArgb((byte)(255 * XMVectorGetW(rgb)),
                                 (byte)(255 * XMVectorGetX(rgb)),
                                 (byte)(255 * XMVectorGetY(rgb)),
                                 (byte)(255 * XMVectorGetZ(rgb)));
}

void HslColorSelector::RgbToHsl(Windows::UI::Color color, int *ph, int *ps, int *pl)
{
    XMVECTOR rgb = XMVectorSet(color.R / 255.0f, color.G / 255.0f, color.B / 255.0f, color.A / 255.0f);
    XMVECTOR hsl = XMColorRGBToHSL(rgb);
    *ph = (int)(255 * XMVectorGetX(hsl));
    *ps = (int)(255 * XMVectorGetY(hsl));
    *pl = (int)(255 * XMVectorGetZ(hsl));
}

