//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace Posterizer;

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

    masks[0] = 0xFF;
    masks[1] = 0xFF;
    masks[2] = 0xFF;

    Loaded += ref new RoutedEventHandler(this, &MainPage::OnLoaded);
}

void MainPage::OnLoaded(Object^ sender, RoutedEventArgs^ args)
{
    // Create the RadioButton controls
    // NOTE: 'a' here means "All" not "alpha"!
    static wchar_t prefix[] = { 'r', 'g', 'b', 'a' };

    for (int col = 0; col < 4; col++)
        for (int row = 1; row < 9; row++)
        {
            RadioButton^ radio = ref new RadioButton();
            radio->Content = row.ToString();
            radio->Margin = ThicknessHelper::FromLengths(12, 6, 12, 6);
            radio->GroupName = prefix[col].ToString();
            radio->Tag = prefix[col].ToString() + row;
            radio->IsChecked = row == 8;
            radio->Checked += ref new RoutedEventHandler(this, &MainPage::OnRadioButtonChecked);

            Grid::SetColumn(radio, col);
            Grid::SetRow(radio, row);
            controlPanelGrid->Children->Append(radio);
        }
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
        for each (String^ extension in codecInfo->FileExtensions)
            picker->FileTypeFilter->Append(extension);

    // Get the selected file
    task<StorageFile^> pickSingleFileTask = create_task(picker->PickSingleFileAsync());
    pickSingleFileTask.then([this](StorageFile^ storageFile)
    {
        if (storageFile != nullptr)
        {
            // Open the stream and create a decoder
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

                        // Get the source pixels
                        task<PixelDataProvider^> getPixelDataTask = 
                            create_task(bitmapFrame->GetPixelDataAsync(BitmapPixelFormat::Bgra8,
                                                                       BitmapAlphaMode::Premultiplied, 
                                                                       ref new BitmapTransform(), 
                                                                       ExifOrientationMode::RespectExifOrientation, 
                                                                       ColorManagementMode::ColorManageToSRgb));
                        getPixelDataTask.then([this, bitmapFrame](PixelDataProvider^ dataProvider)
                        {
                            srcPixels = dataProvider->DetachPixelData();
                            dstPixels = ref new Array<byte>(srcPixels->Length);

                            // Create WriteableBitmap and set as Image source
                            bitmap = ref new WriteableBitmap(bitmapFrame->PixelWidth, bitmapFrame->PixelHeight);
                            image->Source = bitmap;

                            // Update Bitmap from masked pixels
                            UpdateBitmap();

                            // Enable the other buttons
                            saveAsButton->IsEnabled = true;
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

        for each (String^ extension in codecInfo->FileExtensions)
            extensions->Append(extension);

        wchar_t filetype[100];
        wcscpy_s(filetype, 100, codecInfo->FriendlyName->Data());
        int spaceIndex = wcscspn(filetype, L" ");
        filetype[spaceIndex] = '\0';
        picker->FileTypeChoices->Insert(ref new String(filetype), extensions);

        for each (String^ extension in codecInfo->MimeTypes)
            imageTypes->Insert(extension, codecInfo->CodecId);
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
                                      96, 96, pixels);
                encoder->FlushAsync();
            });
        }
    });
}

void MainPage::OnRadioButtonChecked(Object^ sender, RoutedEventArgs^ args)
{
    // Decode the RadioButton Tag property
    RadioButton^ radio = dynamic_cast<RadioButton^>(sender);
    String^ tag = dynamic_cast<String^>(radio->Tag);
    int maskIndex = -1;
    int bits = _wtoi(tag->Data() + 1);  // 1 to 8
    byte mask = (byte)(0xFF << (8 - bits));
    bool needsUpdate = false;

    switch (tag->Data()[0])
    {
    case 'r': maskIndex = 2; break;
    case 'g': maskIndex = 1; break;
    case 'b': maskIndex = 0; break;
    }

    // For "All", check all the other buttons in the row
    if (tag->Data()[0] == 'a')
    {
        needsUpdate = masks[0] != mask && masks[1] != mask && masks[2] != mask;

        if (needsUpdate)
            masks[0] = masks[1] = masks[2] = mask;

        for each (UIElement^ child in (dynamic_cast<Panel^>(radio->Parent))->Children)
        {
            RadioButton^ radioChild = dynamic_cast<RadioButton^>(child);

            if (radioChild != nullptr && radioChild != radio && Grid::GetRow(radioChild) == Grid::GetRow(radio))
            {
                radioChild->IsChecked = true;
            }
        }
    }
    else
    {
        needsUpdate = masks[maskIndex] != mask;

        if (needsUpdate)
            masks[maskIndex] = mask;
    }

    if (needsUpdate)
        UpdateBitmap();
}

void MainPage::OnCheckBoxChecked(Object^ sender, RoutedEventArgs^ args)
{
    UpdateBitmap();
}

void MainPage::UpdateBitmap()
{
    if (bitmap == nullptr)
        return;

    for (unsigned int index = 0; index < srcPixels->Length; index += 4)
    {
        // Mask source pixels
        byte B = (byte)(masks[0] & srcPixels[index + 0]);
        byte G = (byte)(masks[1] & srcPixels[index + 1]);
        byte R = (byte)(masks[2] & srcPixels[index + 2]);
        byte A = srcPixels[index + 3];

        // Possibly convert to gray shade
        if (monochromeCheckBox->IsChecked->Value)
        {
            B = (byte)(0.30 * R + 0.59 * G + 0.11 * B);
            G = B;
            R = B;
        }

        // Save destination pixels
        dstPixels[index + 0] = B;
        dstPixels[index + 1] = G;
        dstPixels[index + 2] = R;
        dstPixels[index + 3] = A;
    }

    // Update bitmap
    byte * pBitmap = GetPixelPointer(bitmap);

    for (unsigned int i = 0; i < dstPixels->Length; i++)
        *(pBitmap + i) = dstPixels[i];

    bitmap->Invalidate();
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

