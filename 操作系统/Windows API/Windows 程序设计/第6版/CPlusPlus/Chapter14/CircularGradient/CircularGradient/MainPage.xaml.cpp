//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h" // includes wrl.h and robuffer.h
#include "MainPage.xaml.h"

using namespace CircularGradient;

using namespace Microsoft::WRL;
using namespace Platform;
using namespace Windows::Storage::Streams;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Media::Imaging;

MainPage::MainPage()
{
    InitializeComponent();
    Loaded += ref new RoutedEventHandler(this, &MainPage::OnMainPageLoaded);
}

void MainPage::OnMainPageLoaded(Object^ sender, RoutedEventArgs^ args)
{
    // Create bitmap and get pixel buffer
    WriteableBitmap^ bitmap = ref new WriteableBitmap(256, 256);
    IBuffer^ buffer = bitmap->PixelBuffer;

    // Obtain IBufferByteAccess
    ComPtr<IBufferByteAccess> pBufferByteAccess;
    ComPtr<IUnknown> pBuffer((IUnknown*)buffer);
    pBuffer.As(&pBufferByteAccess);

    // Get pointer to pixel bytes
    byte* pixels;
    pBufferByteAccess->Buffer(&pixels);

    int index = 0;
    int centerX = bitmap->PixelWidth / 2;
    int centerY = bitmap->PixelHeight / 2;
    double pi = 3.14159;

    // Set the pixels
    for (int y = 0; y < bitmap->PixelWidth; y++)
        for (int x = 0; x < bitmap->PixelHeight; x++)
        {
            double angle = 
                std::atan2(((double)y - centerY) / bitmap->PixelHeight,
                           ((double)x - centerX) / bitmap->PixelWidth);
            double fraction = angle / (2 * pi);
            pixels[index++] = (byte)(fraction * 255);       // Blue
            pixels[index++] = 0;                            // Greeen
            pixels[index++] = (byte)(255 * (1 - fraction)); // Red
            pixels[index++] = 255;                          // Alpha
        }

    // Invalidate the WriteableBitmap and set as Image source
    bitmap->Invalidate();
    imageBrush->ImageSource = bitmap;
}