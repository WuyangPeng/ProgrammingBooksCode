//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"    // includes wrl.h, robuffer.h, ppltasks.h
#include "MainPage.xaml.h"

using namespace ReflectedAlphaImage;

using namespace Concurrency;
using namespace Microsoft::WRL;
using namespace Platform;
using namespace Windows::Foundation;
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
    Uri^ uri = ref new Uri("http://www.charlespetzold.com/pw6/PetzoldJersey.jpg");
    RandomAccessStreamReference^ streamRef = RandomAccessStreamReference::CreateFromUri(uri);

    // Read the entire file
    task<IRandomAccessStreamWithContentType^> openReadTask = create_task(streamRef->OpenReadAsync());
    openReadTask.then([this](IRandomAccessStreamWithContentType^ fileStream)
    {
        // Create a buffer for reading the stream
        Buffer^ buffer = ref new Buffer((unsigned int)fileStream->Size);

        task<IBuffer^> readTask = create_task(fileStream->ReadAsync(buffer, (unsigned int)fileStream->Size, InputStreamOptions::None));
        readTask.then([this](IBuffer^ buffer)
        {
            // Create a memory stream for transferring the data
            InMemoryRandomAccessStream^ memoryStream = ref new InMemoryRandomAccessStream();

            task<unsigned int> writeTask = create_task(memoryStream->WriteAsync(buffer));
            writeTask.then([this, memoryStream](unsigned int sent)
            {
                memoryStream->Seek(0);

                // Create WriteableBitmap with unknown size
                WriteableBitmap^ bitmap = ref new WriteableBitmap(1, 1);

                // Use the memory stream as the Bitmap source
                bitmap->SetSource(memoryStream);

                // Get access to the pixels
                IBuffer^ buffer = bitmap->PixelBuffer;

                // Obtain IBufferByteAccess
                ComPtr<IBufferByteAccess> pBufferByteAccess;
                ComPtr<IUnknown> pBuffer((IUnknown*)buffer);
                pBuffer.As(&pBufferByteAccess);
    
                // Get pointer to pixel bytes
                byte* pixels;
                pBufferByteAccess->Buffer(&pixels);
                int index = 0;

                // Apply opacity to the pixels
                for (int y = 0; y < bitmap->PixelHeight; y++)
                {
                    double opacity = (double)y / bitmap->PixelHeight;

                    for (int x = 0; x < bitmap->PixelWidth; x++)
                        for (int i = 0; i < 4; i++)
                        {
                            pixels[index] = (byte)(opacity * pixels[index]);
                            index++;
                        }
                }

                // Invalidate the WriteableBitmap and set as Image source
                bitmap->Invalidate();
                reflectedImage->Source = bitmap;
            });
        });
    });
}