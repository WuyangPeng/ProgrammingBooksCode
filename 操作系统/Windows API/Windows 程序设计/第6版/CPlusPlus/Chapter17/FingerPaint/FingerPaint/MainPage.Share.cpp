#include "pch.h"
#include "MainPage.xaml.h"

using namespace FingerPaint;

using namespace Concurrency;
using namespace Platform;
using namespace Windows::ApplicationModel::DataTransfer;
using namespace Windows::Foundation;
using namespace Windows::Graphics::Imaging;
using namespace Windows::Storage::Streams;
using namespace Windows::System;
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Media::Imaging;


void MainPage::InitializeSharing()
{
    // Initialize the Past button and provide for updates
    CheckForPasteEnable();
    Clipboard::ContentChanged += ref new EventHandler<Object^>(this, &MainPage::OnClipboardContentChanged);

    // Watch for accelerator keys for Copy and Paste
    Window::Current->CoreWindow->Dispatcher->AcceleratorKeyActivated +=
        ref new TypedEventHandler<CoreDispatcher^, AcceleratorKeyEventArgs^>(this, &MainPage::OnAcceleratorKeyActivated);

    // Hook into the Share pane for providing data
    DataTransferManager::GetForCurrentView()->DataRequested +=
        ref new TypedEventHandler<DataTransferManager^, DataRequestedEventArgs^>(this, &MainPage::OnDataTransferDataRequested);
}

void MainPage::OnDataTransferDataRequested(DataTransferManager^ sender, DataRequestedEventArgs^ args)
{
    DataRequestDeferral^ deferral = args->Request->GetDeferral();

    // Get a stream reference and hand it over
    task<RandomAccessStreamReference^> getBitmapTask = create_task(GetBitmapStream(bitmap));
    getBitmapTask.then([args, deferral] (RandomAccessStreamReference^ streamRef)
    {
        args->Request->Data->SetBitmap(streamRef);
        args->Request->Data->Properties->Title = "Finger Paint";
        args->Request->Data->Properties->Description = "Share this painting with another app";

        deferral->Complete();
    });
}

void MainPage::OnClipboardContentChanged(Object^ sender, Object^ args)
{
    CheckForPasteEnable();
}

void MainPage::CheckForPasteEnable()
{
    pasteAppBarButton->IsEnabled = CheckClipboardForBitmap();
}

bool MainPage::CheckClipboardForBitmap()
{
    DataPackageView^ dataView = Clipboard::GetContent();
    return dataView->Contains(StandardDataFormats::Bitmap);
}

void MainPage::OnCopyAppBarButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    task<RandomAccessStreamReference^> getBitmapTask = create_task(GetBitmapStream(bitmap));
    getBitmapTask.then([this] (RandomAccessStreamReference^ streamRef)
    {
        DataPackage^ dataPackage = ref new DataPackage();
        dataPackage->RequestedOperation = DataPackageOperation::Move;
        dataPackage->SetBitmap(streamRef);
        Clipboard::SetContent(dataPackage);
        this->BottomAppBar->IsOpen = false;
    });
}

task<RandomAccessStreamReference^> MainPage::GetBitmapStream(WriteableBitmap^ bitmap)
{
    // Create a BitmapEncoder associated with a memory stream
    InMemoryRandomAccessStream^ memoryStream = ref new InMemoryRandomAccessStream();
    task<BitmapEncoder^> createEncoderTask = create_task(BitmapEncoder::CreateAsync(BitmapEncoder::PngEncoderId,
                                                                                    memoryStream));
    return createEncoderTask.then([this, bitmap, memoryStream] (BitmapEncoder^ encoder)
    {
        // Create a pixels array for this bitmap
        int length = 4 * bitmap->PixelWidth * bitmap->PixelHeight;
        Array<byte>^ arrPixels = ref new Array<byte>(pixels, length);

        // Set the pixels into that encoder
        encoder->SetPixelData(BitmapPixelFormat::Bgra8,
                              BitmapAlphaMode::Premultiplied,
                              (unsigned int)bitmap->PixelWidth,
                              (unsigned int)bitmap->PixelHeight,
                              96, 96, arrPixels);

        task<void> flushEncoderTask = create_task(encoder->FlushAsync());
        return flushEncoderTask.then([memoryStream] ()
        {
            return RandomAccessStreamReference::CreateFromStream(memoryStream);
        });
    });
}

void MainPage::OnPasteAppBarButtonClick(Platform::Object^ sender, RoutedEventArgs^ args)
{
    // Temporarily disable the Paste button
    pasteAppBarButton->IsEnabled = false;

    // Get the Clipboard contents and check for a bitmap
    DataPackageView^ dataView = Clipboard::GetContent();

    if (dataView->Contains(StandardDataFormats::Bitmap))
    {
        // Get the stream reference and a stream
        task<RandomAccessStreamReference^> getBitmapTask = create_task(dataView->GetBitmapAsync());
        getBitmapTask.then([this] (RandomAccessStreamReference^ streamRef)
        {
            task<IRandomAccessStreamWithContentType^> openReadTask = create_task(streamRef->OpenReadAsync());
            openReadTask.then([this] (IRandomAccessStreamWithContentType^ stream)
            {
                task<BitmapDecoder^> createDecoderTask = create_task(BitmapDecoder::CreateAsync(stream));
                createDecoderTask.then([this] (BitmapDecoder^ decoder)
                {
                    task<BitmapFrame^> getFrameTask = create_task(decoder->GetFrameAsync(0));
                    getFrameTask.then([this] (BitmapFrame^ bitmapFrame)
                    {
                        // Save information for creating WriteableBitmap
                        pastedPixelWidth = (int)bitmapFrame->PixelWidth;
                        pastedPixelHeight = (int)bitmapFrame->PixelHeight;

                        task<PixelDataProvider^> getDataTask = 
                            create_task(bitmapFrame->GetPixelDataAsync(BitmapPixelFormat::Bgra8,
                                                                       BitmapAlphaMode::Premultiplied,
                                                                       ref new BitmapTransform(),
                                                                       ExifOrientationMode::RespectExifOrientation,
                                                                       ColorManagementMode::ColorManageToSRgb));

                        getDataTask.then([this] (PixelDataProvider^ pixelProvider)
                        {
                            // Save information sufficient for creating WriteableBitmap
                            pastedPixels = pixelProvider->DetachPixelData();
                            // Check if it's OK to replace the current painting
                            task<void> checkOkToTrashTask = create_task(CheckIfOkToTrashFile(&MainPage::FinishPasteBitmapAndPixelArray));
                            checkOkToTrashTask.then([this] ()
                            {
                                // Re-enable the button and close th app bar
                                pasteAppBarButton->IsEnabled = true;
                                this->BottomAppBar->IsOpen = false;
                            }, task_continuation_context::use_current());
                        });
                    });
                });
            });
        });
    }
}

Concurrency::task<void> MainPage::FinishPasteBitmapAndPixelArray()
{
    bitmap = ref new WriteableBitmap(pastedPixelWidth, pastedPixelHeight);

    InitializeBitmap();

    // Transfer pixels to bitmap
    int length = 4 * pastedPixelWidth * pastedPixelHeight;

    for (int i = 0; i < length; i++)
        pixels[i] = pastedPixels[i];

    pastedPixels = nullptr;

    // Set AppSettings properties for new image
    appSettings->LoadedFilePath = nullptr;
    appSettings->LoadedFilename = nullptr;
    appSettings->IsImageModified = false;

    return task<void>([] () {});
}

void MainPage::OnAcceleratorKeyActivated(CoreDispatcher^ sender, AcceleratorKeyEventArgs^ args)
{
    if ((args->EventType == CoreAcceleratorKeyEventType::SystemKeyDown ||
         args->EventType == CoreAcceleratorKeyEventType::KeyDown) &&
        (args->VirtualKey == VirtualKey::C || args->VirtualKey == VirtualKey::V))
    {
        CoreWindow^ window = Window::Current->CoreWindow;
        CoreVirtualKeyStates down = CoreVirtualKeyStates::Down;

        // Only want case where Ctrl is down
        if ((window->GetKeyState(VirtualKey::Shift) & down) == down ||
            (window->GetKeyState(VirtualKey::Control) & down) != down ||
            (window->GetKeyState(VirtualKey::Menu) & down) == down)
        {
            return;
        }

        if (args->VirtualKey == VirtualKey::C)
        {
            OnCopyAppBarButtonClick(nullptr, nullptr);
        }
        else if (args->VirtualKey == VirtualKey::V)
        {
            OnPasteAppBarButtonClick(pasteAppBarButton, nullptr);
        }
    }
}
