//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace HarderCameraCapture;

using namespace Concurrency;
using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Platform;
using namespace Windows::Devices::Enumeration;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Graphics::Imaging;
using namespace Windows::Media::Capture;
using namespace Windows::Media::MediaProperties;
using namespace Windows::Storage::Streams;
using namespace Windows::UI;
using namespace Windows::UI::Popups;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Media::Imaging;
using namespace Windows::UI::Xaml::Navigation;

MainPage::MainPage()
{
    InitializeComponent();
    ignoreTaps = false;
    mediaCapture = ref new MediaCapture();
    Loaded += ref new RoutedEventHandler(this, &MainPage::OnMainPageLoaded);
}

void MainPage::OnMainPageLoaded(Object^ sender, RoutedEventArgs^ args)
{
    task<DeviceInformationCollection^> findDevicesTask = 
        create_task(DeviceInformation::FindAllAsync(DeviceClass::VideoCapture));

    findDevicesTask.then([this] (DeviceInformationCollection^ devInfos)
    {
        if (devInfos->Size == 0)
        {
            MessageDialog^ messageDialog = ref new MessageDialog("No video capture devices found");
            task<IUICommand^> showMessageTask = create_task(messageDialog->ShowAsync());
            showMessageTask.then([] (IUICommand^) {});
        }
        else
        {
            String^ id = nullptr;

            // Try to find the front webcam
            for each (DeviceInformation^ devInfo in devInfos)
            {
                if (devInfo->EnclosureLocation != nullptr &&
                    devInfo->EnclosureLocation->Panel == Windows::Devices::Enumeration::Panel::Front)
                {
                    id = devInfo->Id;
                }
            }

            // If not available, just pick the first one
            if (id == nullptr)
            {
                id = devInfos->GetAt(0)->Id;
            }

            // Create initialization setttings
            MediaCaptureInitializationSettings^ settings = ref new MediaCaptureInitializationSettings();
            settings->VideoDeviceId = id;
            settings->StreamingCaptureMode = StreamingCaptureMode::Video;

            // Initialize the MediaCapture device
            task<void> initializeCaptureTask = create_task(mediaCapture->InitializeAsync(settings));
            initializeCaptureTask.then([this] ()
            {
                // Associate with the CaptureElement
                captureElement->Source = mediaCapture.Get();

                // Start the preview
                task<void> startPreviewTask = create_task(mediaCapture->StartPreviewAsync());
                startPreviewTask.then([this] () 
                {
                });
            });
        }
    });
}

void MainPage::OnTapped(TappedRoutedEventArgs^ args)
{
    if (ignoreTaps)
        return;

    // Capture photo to memory stream
    ImageEncodingProperties^ imageEncodingProps = ImageEncodingProperties::CreateJpeg();
    InMemoryRandomAccessStream^ memoryStream = ref new InMemoryRandomAccessStream();
    task<void> capturePhotoTask = create_task(mediaCapture->CapturePhotoToStreamAsync(imageEncodingProps, memoryStream));
    capturePhotoTask.then([this, memoryStream] ()
    {
        // Use BitmapDecoder to get pixels array
        task<BitmapDecoder^> createDecoderTask = create_task(BitmapDecoder::CreateAsync(memoryStream));
        createDecoderTask.then([this] (BitmapDecoder^ decoder)
        {
            task<PixelDataProvider^> getPixelDataTask = create_task(decoder->GetPixelDataAsync());
            getPixelDataTask.then([this, decoder] (PixelDataProvider^ pixelProvider)
            {
                Array<byte>^ srcPixels = pixelProvider->DetachPixelData();

                // Create a WriteableBitmap and get the pixels pointer
                WriteableBitmap^ bitmap = ref new WriteableBitmap((int)decoder->PixelWidth, (int)decoder->PixelHeight);
                IBuffer^ buffer = bitmap->PixelBuffer;
                ComPtr<IBufferByteAccess> pBufferByteAccess;
                ComPtr<IUnknown> pBuffer((IUnknown*)buffer);
                pBuffer.As(&pBufferByteAccess);
                byte* pDstPixels;
                pBufferByteAccess->Buffer(&pDstPixels);

                // Saturate the colors
                for (unsigned int index = 0; index < srcPixels->Length; index += 4)
                {
                    XMVECTOR rgb = XMVectorSet(srcPixels[index + 2] / 255.0f,   // red
                                               srcPixels[index + 1] / 255.0f,   // green       
                                               srcPixels[index + 0] / 255.0f,   // blue
                                               srcPixels[index + 3] / 255.0f);  // alpha

                    // Set saturation to maximum
                    XMVECTOR hsl = XMColorRGBToHSL(rgb);
                    hsl = XMVectorSetY(hsl, 1.0f);
                    rgb = XMColorHSLToRGB(hsl);

                    pDstPixels[index + 0] = (byte)(255 * XMVectorGetZ(rgb));    // blue
                    pDstPixels[index + 1] = (byte)(255 * XMVectorGetY(rgb));    // green
                    pDstPixels[index + 2] = (byte)(255 * XMVectorGetX(rgb));    // red;
                    pDstPixels[index + 3] = (byte)(255 * XMVectorGetW(rgb));    // alpha;
                }
                bitmap->Invalidate();

                // Display the bitmap
                image->Source = bitmap;
 
                // Set a timer for the image
                DispatcherTimer^ timer = ref new DispatcherTimer();
                TimeSpan interval = { 25000000 };
                timer->Interval = interval;
                timerTickEventToken = timer->Tick += ref new EventHandler<Object^>(this, &MainPage::OnTimerTick);
                timer->Start();

                ignoreTaps = true;
            });
        });
    });
}

void MainPage::OnTimerTick(Object^ sender, Object^ args)
{
    // Disable the timer
    DispatcherTimer^ timer = dynamic_cast<DispatcherTimer^>(sender);
    timer->Stop();
    timer->Tick -= timerTickEventToken;

    // Get rid of the bitmap
    image->Source = nullptr;
    ignoreTaps = false;
}