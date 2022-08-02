//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h" // includes wrl.h and robuffer.h
#include "MainPage.xaml.h"

using namespace CustomGradient;

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

    // Set the pixels
    for (int y = 0; y < bitmap->PixelWidth; y++)
        for (int x = 0; x < bitmap->PixelHeight; x++)
        {
            int index = 4 * (y * bitmap->PixelWidth + x);
            pixels[index + 0] = (byte)x;    // Blue
            pixels[index + 1] = 0;          // Greeen
            pixels[index + 2] = (byte)y;    // Red
            pixels[index + 3] = 255;        // Alpha
        }

    // Invalidate the WriteableBitmap and set as Image source
    bitmap->Invalidate();
    image->Source = bitmap;
}