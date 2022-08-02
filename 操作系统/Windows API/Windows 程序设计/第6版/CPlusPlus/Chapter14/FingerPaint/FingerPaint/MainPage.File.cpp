//
// MainPage.File.cpp
// Partial implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace FingerPaint;

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
using namespace Windows::UI;
using namespace Windows::UI::Input;
using namespace Windows::UI::Popups;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Media::Imaging;
using namespace Windows::UI::Xaml::Navigation;

task<void> MainPage::CreateNewBitmapAndPixelArray()
{
    bitmap = ref new WriteableBitmap((int)this->ActualWidth, (int)this->ActualHeight);

    InitializeBitmap();

    // Set whole bitmap to white
    int length = 4 * bitmap->PixelWidth * bitmap->PixelHeight;
    for (int index = 0; index < length; index++)
        pixels[index] = 0xFF;

    // Invalidate the WriteableBitmap
    bitmap->Invalidate();

    // Set application settings
    appSettings->LoadedFilePath = nullptr;
    appSettings->LoadedFilename = nullptr;
    appSettings->IsImageModified = false;

    return task<void>([] () {});
}

task<void> MainPage::LoadBitmapFromFile()
{
    StorageFolder^ localFolder = ApplicationData::Current->LocalFolder;
    task<StorageFile^> getFileTask = create_task(localFolder->GetFileAsync("FingerPaint.png"));
    return getFileTask.then([this] (StorageFile^ storageFile)
    {
        task<void> loadBitmapTask = create_task(LoadBitmapFromFile(storageFile));
        loadBitmapTask.then([] ()
        {
        });
    });
}

task<void> MainPage::LoadBitmapFromFile(StorageFile^ storageFile)
{
    task<IRandomAccessStreamWithContentType^> openReadTask = create_task(storageFile->OpenReadAsync());
   
    return openReadTask.then([this](IRandomAccessStreamWithContentType^ stream)
    {
        task<BitmapDecoder^> createDecoderTask = create_task(BitmapDecoder::CreateAsync(stream));
        createDecoderTask.then([this] (BitmapDecoder^ decoder)
        {
            task<BitmapFrame^> getFrameTask = create_task(decoder->GetFrameAsync(0));
            getFrameTask.then([this](BitmapFrame^ bitmapFrame)
            {
                task<PixelDataProvider^> getPixelDataTask = 
                    create_task(bitmapFrame->GetPixelDataAsync(BitmapPixelFormat::Bgra8,
                                                               BitmapAlphaMode::Premultiplied,
                                                               ref new BitmapTransform(),
                                                               ExifOrientationMode::RespectExifOrientation,
                                                               ColorManagementMode::ColorManageToSRgb));
                getPixelDataTask.then([this, bitmapFrame](PixelDataProvider^ dataProvider)
                {
                    Array<byte>^ pSrcPixels = dataProvider->DetachPixelData();
                    bitmap = ref new WriteableBitmap((int)bitmapFrame->PixelWidth,
                                                     (int)bitmapFrame->PixelHeight);
                    InitializeBitmap();

                    for (unsigned int i = 0; i < pSrcPixels->Length; i++)
                        pixels[i] = pSrcPixels[i];
                });
            });
        });
    });
}

void MainPage::InitializeBitmap()
{
    // Obtain IBufferByteAccess
    IBuffer^ buffer = bitmap->PixelBuffer;
    ComPtr<IBufferByteAccess> pBufferByteAccess;
    ComPtr<IUnknown> pBuffer((IUnknown*)buffer);
    pBuffer.As(&pBufferByteAccess);

    // Get pointer to pixel bytes
    pBufferByteAccess->Buffer(&pixels);

    // Set to Image element
    image->Source = bitmap;
    CalculateImageScaleAndOffset();
}

void MainPage::OnAddAppBarButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    Button^ button = dynamic_cast<Button^>(sender);
    button->IsEnabled = false;

    task<void> checkIfOkToTrashTask = 
        create_task(MainPage::CheckIfOkToTrashFile(&MainPage::CreateNewBitmapAndPixelArray));
    checkIfOkToTrashTask.then([this, button] ()
    {
        button->IsEnabled = true;
        this->BottomAppBar->IsOpen = false;
    }, task_continuation_context::use_current());
}

void MainPage::OnOpenAppBarButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    Button^ button = dynamic_cast<Button^>(sender);
    button->IsEnabled = false;

    task<void> checkIfOkToTrashTask = 
        create_task(MainPage::CheckIfOkToTrashFile(&MainPage::LoadFileFromOpenPicker));
    checkIfOkToTrashTask.then([this, button] ()
    {
        button->IsEnabled = true;
        this->BottomAppBar->IsOpen = false;
    });
}

task<void> MainPage::CheckIfOkToTrashFile(task<void> (MainPage::*commandAction)(void))
{
    if (!appSettings->IsImageModified)
    {
        return (this->*commandAction)();
    }

    String^ message = "Do you want to save changes to " +
        (appSettings->LoadedFilePath == nullptr ? "(untitled)" : appSettings->LoadedFilePath) + "?";

    MessageDialog^ msgdlg = ref new MessageDialog(message, "Finger Paint");
    msgdlg->Commands->Append(ref new UICommand("Save", nullptr, "save"));
    msgdlg->Commands->Append(ref new UICommand("Don't save", nullptr, "dont"));
    msgdlg->Commands->Append(ref new UICommand("Cancel", nullptr, "cancel"));
    msgdlg->DefaultCommandIndex = 0;
    msgdlg->CancelCommandIndex = 2;

    task<IUICommand^> messageDialogShowTask(msgdlg->ShowAsync());
    return messageDialogShowTask.then([this, commandAction] (IUICommand^ command)
    {
        String^ strCommand = dynamic_cast<String^>(command->Id);

        if (strCommand == "cancel")
            return task<void>([]{});

        if (strCommand == "dont")
            return (this->*commandAction)();

        // Need to save file -- can do so directly with filename
        if (appSettings->LoadedFilePath != nullptr)
        {
            task<bool> saveToFileTask(MainPage::SaveWithErrorNotification(appSettings->LoadedFilePath));
            return saveToFileTask.then([this,commandAction] (bool success)
            {
                if (success)
                    return (this->*commandAction)();
                else
                    return task<void>([]{});
            });
        }

        // Otherwise need to get file from picker
        task<StorageFile^> getFileTask = create_task(MainPage::GetFileFromSavePicker());
        return getFileTask.then([this,commandAction](StorageFile^ storageFile)
        {
            if (storageFile == nullptr)
                return task<void>([]{});;

            task<bool> saveToFileTask(MainPage::SaveWithErrorNotification(storageFile));
            return saveToFileTask.then([this,commandAction] (bool success)
            {
                if (success)
                    return (this->*commandAction)();
                else
                    return task<void>([]{});
            });
        });
    });
}

task<void> MainPage::LoadFileFromOpenPicker()
{
    // Create FileOpenPicker
    FileOpenPicker^ picker = ref new FileOpenPicker();
    picker->SuggestedStartLocation = PickerLocationId::PicturesLibrary;

    // Initialize with filename extensions
    IVectorView<BitmapCodecInformation^>^ codecInfos = BitmapDecoder::GetDecoderInformationEnumerator();

    for each (BitmapCodecInformation^ codecInfo in codecInfos)
        for each (String^ extension in codecInfo->FileExtensions)
            picker->FileTypeFilter->Append(extension);

    // Get the selected file
    task<StorageFile^> pickFileTask = create_task(picker->PickSingleFileAsync());
    return pickFileTask.then([this] (StorageFile^ storageFile)
    {
        if (storageFile != nullptr)
        {
            task<void> loadBitmapTask = create_task(LoadBitmapFromFile(storageFile));
            loadBitmapTask.then([this, storageFile] (task<void> thisTask)
            {
                Exception^ exception = nullptr;

                try
                {
                    thisTask.get();
                }
                catch (Exception^ exc)
                {
                    exception = exc;
                }

                if (exception != nullptr)
                {
                    MessageDialog^ msgdlg = 
                        ref new MessageDialog("The image file could not be loaded. " +
                                              "The system reports an error of: " + exception,
                                              "Finger Paint"); 
                    task<IUICommand^> msgdlgShowTask = create_task(msgdlg->ShowAsync());
                    msgdlgShowTask.then([](IUICommand^)
                    {
                        return;
                    });
                 }
                 appSettings->LoadedFilePath = storageFile->Path;
                 appSettings->LoadedFilename = storageFile->Name;
                 appSettings->IsImageModified = false; 
            });
        }
    });
}

void MainPage::OnSaveAppBarButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    Button^ button = dynamic_cast<Button^>(sender);
    button->IsEnabled = false;

    if (appSettings->LoadedFilePath != nullptr)
    {
        task<bool> saveFileTask = create_task(SaveWithErrorNotification(appSettings->LoadedFilePath));
        saveFileTask.then([button] (bool)
        {
            button->IsEnabled = true;
        });
    }
    else
    {
        task<StorageFile^> getFileTask = create_task(GetFileFromSavePicker());
        getFileTask.then([this, button] (StorageFile^ storageFile)
        {
            if (storageFile != nullptr)
            {
                task<bool> saveFileTask = create_task(SaveWithErrorNotification(storageFile));
                saveFileTask.then([button] (bool) 
                {
                    button->IsEnabled = true;
                });
            }
        });
    }
}

void MainPage::OnSaveAsAppBarButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    task<StorageFile^> getFileTask = create_task(GetFileFromSavePicker());
    getFileTask.then([this] (StorageFile^ storageFile)
    {
        if (storageFile != nullptr)
        {
            task<bool> saveFileTask = create_task(SaveWithErrorNotification(storageFile));
            saveFileTask.then([] (bool) 
            {
            });
        }
    });
}

task<StorageFile^> MainPage::GetFileFromSavePicker()
{
    FileSavePicker^ picker = ref new FileSavePicker();
    picker->SuggestedStartLocation = PickerLocationId::PicturesLibrary;
    picker->SuggestedFileName = appSettings->LoadedFilename == nullptr ? "MyFingerPainting" : appSettings->LoadedFilename;

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

        for each (String^ mimeType in codecInfo->MimeTypes)
            imageTypes->Insert(mimeType, codecInfo->CodecId);
    }

    task<StorageFile^> pickFileTask = create_task(picker->PickSaveFileAsync());
    return pickFileTask;
}

task<bool> MainPage::SaveWithErrorNotification(String^ filename)
{
    task<StorageFile^> getFileTask = create_task(StorageFile::GetFileFromPathAsync(filename));
    return getFileTask.then([this] (StorageFile^ storageFile)
    {
        task<bool> saveFileTask = create_task(SaveWithErrorNotification(storageFile));
        return saveFileTask.then([] (bool success)
        {
            return success;
        });
    });
}

task<bool> MainPage::SaveWithErrorNotification(StorageFile^ storageFile)
{
    task<void> saveBitmapTask = create_task(SaveBitmapToFile(storageFile));
    return saveBitmapTask.then([this, storageFile] (task<void> thisTask)
    {
        String^ exception = nullptr;

        try
        {
            thisTask.get();
        }
        catch (Exception^ exc)
        {
            exception = exc->Message;
        }

        if (exception != nullptr)
        {
            MessageDialog^ msgdlg =
                ref new MessageDialog("The image file could not be saved. " +
                                      "The system reports an error of: " + exception,
                                      "Finger Paint");
            task<IUICommand^> msgdlgShowTask = create_task(msgdlg->ShowAsync());
            msgdlgShowTask.then([] (IUICommand^)
            {
                return false;
            });
        }

        appSettings->LoadedFilename = storageFile->Name;
        appSettings->LoadedFilePath = storageFile->Path;
        appSettings->IsImageModified = false;
        return true;
    });
}

task<void> MainPage::SaveBitmapToFile()
{
    StorageFolder^ localFolder = ApplicationData::Current->LocalFolder;
    task<StorageFile^> createFileTask = create_task(localFolder->CreateFileAsync("FingerPaint.png",
                                                                                 CreationCollisionOption::ReplaceExisting));
    return createFileTask.then([this](StorageFile^ storageFile)
    {
        task<void> saveBitmapTask = create_task(SaveBitmapToFile(storageFile));
        return saveBitmapTask.then([] ()
        {
        });
    });
}

task<void> MainPage::SaveBitmapToFile(String^ filename)
{
    task<StorageFile^> getFileTask = create_task(StorageFile::GetFileFromPathAsync(filename));
    return getFileTask.then([this] (StorageFile^ storageFile)
    {
        task<void> saveBitmapTask = create_task(SaveBitmapToFile(storageFile));
        return saveBitmapTask.then([] ()
        {
        });
    });
}

task<void> MainPage::SaveBitmapToFile(StorageFile^ storageFile)
{
    task<IRandomAccessStream^> openFileTask = create_task(storageFile->OpenAsync(FileAccessMode::ReadWrite));
    return openFileTask.then([this] (IRandomAccessStream^ stream)
    {
        task<BitmapEncoder^> createEncoderTask = create_task(BitmapEncoder::CreateAsync(BitmapEncoder::PngEncoderId, stream));
        return createEncoderTask.then([this] (BitmapEncoder^ encoder)
        {
            unsigned int arraySize = 4 * bitmap->PixelWidth * bitmap->PixelHeight;
            Array<byte>^ pixelArray = ref new Array<byte>(pixels, arraySize);

            encoder->SetPixelData(BitmapPixelFormat::Bgra8,
                                  BitmapAlphaMode::Premultiplied,
                                  (unsigned int)bitmap->PixelWidth,
                                  (unsigned int)bitmap->PixelHeight,
                                  96, 96,
                                  pixelArray); // ref new Array<byte>(pixels, arraySize));

            task<void> flushTask = create_task(encoder->FlushAsync());
            return flushTask.then([] ()
            {
                return;
            });
        });
    });
}

