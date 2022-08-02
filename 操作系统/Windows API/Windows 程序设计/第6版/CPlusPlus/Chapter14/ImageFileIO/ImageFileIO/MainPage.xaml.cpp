//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"    // includes wrl.h, robuffer.h, and ppltasks.h
#include "MainPage.xaml.h"

using namespace ImageFileIO;

using namespace Concurrency;
using namespace Microsoft::WRL;
using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Graphics::Imaging;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;
using namespace Windows::Storage::Streams;
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
}

void MainPage::OnOpenAppBarButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    // Create FileOpenPicker
    FileOpenPicker^ picker = ref new FileOpenPicker();
    picker->SuggestedStartLocation = PickerLocationId::PicturesLibrary;

    // Initialize with filename extensions
    IVectorView<BitmapCodecInformation^>^ codecInfos = 
                        BitmapDecoder::GetDecoderInformationEnumerator();

    for each (BitmapCodecInformation^ codecInfo in codecInfos)
       for (unsigned int i = 0; i < codecInfo->FileExtensions->Size; i++)
            picker->FileTypeFilter->Append(codecInfo->FileExtensions->GetAt(i));

    task<StorageFile^> pickSingleFileTask = create_task(picker->PickSingleFileAsync());
    pickSingleFileTask.then([this](StorageFile^ storageFile)
    {
        if (storageFile != nullptr)
        {
            task<IRandomAccessStreamWithContentType^> openReadTask = create_task(storageFile->OpenReadAsync());
            openReadTask.then([](IRandomAccessStreamWithContentType^ stream)
            {
                return task<BitmapDecoder^> (BitmapDecoder::CreateAsync(stream));
            })
            .then([this, storageFile] (task<BitmapDecoder^> thisTask)
            {
                BitmapDecoder^ decoder;
                String^ exception;

                try
                {
                    decoder = thisTask.get();
                }
                catch (Exception^ exc)
                {
                    exception = exc->Message;
                }

                if (exception != nullptr)
                {
                    MessageDialog^ msgdlg = 
                        ref new MessageDialog("That particular image file could not be loaded. " +
                                              "The System reports an error of: " + exception);

                    task<IUICommand^> messageDialogShowTask = create_task(msgdlg->ShowAsync());
                    messageDialogShowTask.then([] (IUICommand^ uiCommand) {});
                }
                else
                {
                    // Get the first frame
                    task<BitmapFrame^> getFrameTask = create_task(decoder->GetFrameAsync(0));
                    getFrameTask.then([this, storageFile](BitmapFrame^ bitmapFrame)
                    {
                        // Set information title
                        txtblk->Text = storageFile->Name + ": " +
                                       bitmapFrame->PixelWidth.ToString() + " x " +
                                       bitmapFrame->PixelHeight.ToString() + " " +
                                       bitmapFrame->BitmapPixelFormat.ToString() + " " +
                                       bitmapFrame->DpiX.ToString() + " x " +
                                       bitmapFrame->DpiY.ToString() + " DPI";

                        // Save the resolution
                        dpiX = bitmapFrame->DpiX;
                        dpiY = bitmapFrame->DpiY;

                        task<PixelDataProvider^> getPixelDataTask = create_task(bitmapFrame->GetPixelDataAsync(BitmapPixelFormat::Bgra8,
                                                                                                 BitmapAlphaMode::Premultiplied, 
                                                                                                 ref new BitmapTransform(), 
                                                                                                 ExifOrientationMode::RespectExifOrientation, 
                                                                                                 ColorManagementMode::ColorManageToSRgb));
                        getPixelDataTask.then([this, bitmapFrame](PixelDataProvider^ dataProvider)
                        {
                            Array<byte>^ filePixels = dataProvider->DetachPixelData();

                            // Create WriteableBitmap and set the pixels
                            WriteableBitmap^ bitmap = ref new WriteableBitmap(bitmapFrame->PixelWidth, bitmapFrame->PixelHeight);

                            // Is there a way to create an output stream from the 
                            //      bitmap IBuffer so the bytes can be transferred
                            //      through DataWriter.WriteBytes?

                            // Obtain IBufferByteAccess
                            ComPtr<IBufferByteAccess> pBufferByteAccess;
                            ComPtr<IUnknown> pBuffer((IUnknown*)bitmap->PixelBuffer);
                            pBuffer.As(&pBufferByteAccess);

                            // Get pointer to pixel bytes
                            byte* pixels;
                            pBufferByteAccess->Buffer(&pixels);

                            // Transfer the pixels
                            for (unsigned int i = 0; i < filePixels->Length; i++)
                                pixels[i] = filePixels[i];

                            // Invalidate the WriteableBitmap and set as Image source
                            bitmap->Invalidate();
                            image->Source = bitmap;

                            // Enable the other buttons
                            saveAsButton->IsEnabled = true;
                            rotateLeftButton->IsEnabled = true;
                            rotateRightButton->IsEnabled = true;
                        });
                    });
                }
            });
        }
    });
}

void MainPage::OnSaveAsAppBarButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    FileSavePicker^ picker = ref new FileSavePicker();
    picker->SuggestedStartLocation = PickerLocationId::PicturesLibrary;

    // Get the encoder information
    Map<String^, Guid>^ imageTypes = ref new Map<String^, Guid>();
    IVectorView<BitmapCodecInformation^>^ codecInfos = 
                        BitmapEncoder::GetEncoderInformationEnumerator();

    for each (BitmapCodecInformation^ codecInfo in codecInfos)
    {
        Vector<String^>^ extensions = ref new Vector<String^>();

        for (unsigned int i = 0; i < codecInfo->FileExtensions->Size; i++)
            extensions->Append(codecInfo->FileExtensions->GetAt(i));

        wchar_t filetype[100];
        wcscpy_s(filetype, 100, codecInfo->FriendlyName->Data());
        int spaceIndex = wcscspn(filetype, L" ");
        filetype[spaceIndex] = '\0';
        picker->FileTypeChoices->Insert(ref new String(filetype), extensions);

        for (unsigned int i = 0; i < codecInfo->MimeTypes->Size; i++)
            imageTypes->Insert(codecInfo->MimeTypes->GetAt(i), codecInfo->CodecId);
    }

    // Get a selected StorageFile
    task<StorageFile^> pickSaveFileTask = create_task(picker->PickSaveFileAsync());
    pickSaveFileTask.then([this, imageTypes](StorageFile^ storageFile)
    {
        if (storageFile != nullptr)
        {
            task<IRandomAccessStream^> openTask = create_task(storageFile->OpenAsync(FileAccessMode::ReadWrite));
            openTask.then([this, storageFile, imageTypes](IRandomAccessStream^ fileStream)
            {
                // Create an encoder
                Guid codecId = imageTypes->Lookup(storageFile->ContentType);

                return BitmapEncoder::CreateAsync(codecId, fileStream);
            })
            .then([this] (BitmapEncoder^ encoder)
            {
                // Get the pixels from the existing WriteableBitmap
                WriteableBitmap^ bitmap = dynamic_cast<WriteableBitmap^>(image->Source);
                DataReader^ dataReader = DataReader::FromBuffer(bitmap->PixelBuffer);
                Array<byte>^ pixels = ref new Array<byte>(bitmap->PixelBuffer->Length);
                dataReader->ReadBytes(pixels);

                encoder->SetPixelData(BitmapPixelFormat::Bgra8,
                                      BitmapAlphaMode::Premultiplied,
                                      (unsigned int)bitmap->PixelWidth, 
                                      (unsigned int)bitmap->PixelHeight,
                                      dpiX, dpiY, pixels);
                encoder->FlushAsync();
            });
        }
    });
}

void MainPage::OnRotateLeftAppBarButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    Rotate([](BitmapSource^ bitmap, int x, int y)
    {
        return 4 * (bitmap->PixelWidth * x + (bitmap->PixelWidth - y - 1));
    });
}

void MainPage::OnRotateRightAppBarButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    Rotate([](BitmapSource^ bitmap, int x, int y)
    {
        return 4 * (bitmap->PixelWidth * (bitmap->PixelHeight - x - 1) + y);
    });
}

void MainPage::Rotate(int (*calculateSourceIndex)(BitmapSource^, int, int))
{
    // Get the source pixels pointer
    WriteableBitmap^ srcBitmap = dynamic_cast<WriteableBitmap^>(image->Source);
    byte* srcPixels = GetPixelPointer(srcBitmap);

    // Create a destination bitmap and pixel pointer
    WriteableBitmap^ dstBitmap = ref new WriteableBitmap(srcBitmap->PixelHeight, srcBitmap->PixelWidth);
    byte* dstPixels = GetPixelPointer(dstBitmap);

    // Transfer the pixels
    int dstIndex = 0;
    for (int y = 0; y < dstBitmap->PixelHeight; y++)
        for (int x = 0; x < dstBitmap->PixelWidth; x++)
        {
            int srcIndex = calculateSourceIndex(srcBitmap, x, y);

            for (int i = 0; i < 4; i++)
                dstPixels[dstIndex++] = srcPixels[srcIndex++];
        }

    // Swap the DPIs
    std::swap(dpiX, dpiY);

    // Display the new bitmap
    image->Source = dstBitmap;
}

byte * MainPage::GetPixelPointer(WriteableBitmap^ bitmap)
{
    ComPtr<IBufferByteAccess> pBufferByteAccess;
    ComPtr<IUnknown> pBuffer((IUnknown*)bitmap->PixelBuffer);
    pBuffer.As(&pBufferByteAccess);
    byte* pixels;
    pBufferByteAccess->Buffer(&pixels);
    return pixels;
}
