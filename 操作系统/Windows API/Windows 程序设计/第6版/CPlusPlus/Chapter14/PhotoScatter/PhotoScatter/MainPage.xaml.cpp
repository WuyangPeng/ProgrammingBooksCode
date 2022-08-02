//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "ImageType.h"

using namespace PhotoScatter;

using namespace Concurrency;
using namespace Microsoft::WRL;
using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Graphics::Imaging;
using namespace Windows::Storage;
using namespace Windows::Storage::FileProperties;
using namespace Windows::Storage::Streams;
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
    srand(int(time(NULL)));
    Loaded += ref new RoutedEventHandler(this, &MainPage::OnMainPageLoaded);
}

void MainPage::OnMainPageLoaded(Object^ sender, RoutedEventArgs^ args)
{
    StorageFolder^ storageFolder = KnownFolders::PicturesLibrary;
    BuildFolderListBox(storageFolder, 0);
    folderListBox->SelectedIndex = 0;
}

void MainPage::BuildFolderListBox(StorageFolder^ parentStorageFolder, int level)
{
    FolderItem^ folderItem = ref new FolderItem();
    folderItem->StorageFolder = parentStorageFolder;
    folderItem->Level = level;
    folderListBox->Items->Append(folderItem);

    task<IVectorView<StorageFolder^>^> getFoldersTask = create_task(parentStorageFolder->GetFoldersAsync());
    getFoldersTask.then([this, level](IVectorView<StorageFolder^>^ storageFolders)
    {
        for each (StorageFolder^ storageFolder in storageFolders)
            BuildFolderListBox(storageFolder, level + 1);
    });
}

void MainPage::OnFolderListBoxSelectionChanged(Object^ sender, SelectionChangedEventArgs^ args)
{
    FolderItem^ folderItem = dynamic_cast<FolderItem^>(dynamic_cast<ListBox^>(sender)->SelectedItem);

    if (folderItem == nullptr)
    {
        displayBorder->Child = nullptr;
        return;
    }

    if (folderItem->DisplayGrid != nullptr)
    {
        displayBorder->Child = folderItem->DisplayGrid;
        return;
    }

    Grid^ displayGrid = ref new Grid();
    folderItem->DisplayGrid = displayGrid;
    displayBorder->Child = displayGrid;

    StorageFolder^ storageFolder = folderItem->StorageFolder;
    task<IVectorView<StorageFile^>^> getFilesTask = create_task(storageFolder->GetFilesAsync());
    getFilesTask.then([this, displayGrid](IVectorView<StorageFile^>^ storageFiles)
    {
        for each (StorageFile^ storageFile in storageFiles)
        {
            task<StorageItemThumbnail^> getThumbnailTask = create_task(storageFile->GetThumbnailAsync(ThumbnailMode::SingleItem));
            getThumbnailTask.then([this](StorageItemThumbnail^ thumbnail)
            {
                return LoadBitmapAsync(thumbnail);
            })
            .then([this, displayGrid, storageFile](WriteableBitmap^ bitmap)
            {
                if (bitmap != nullptr)
                {
                    // Create new Image element to display the thumbnail
                    Image^ image = ref new Image();
                    image->Source = bitmap;
                    image->Stretch = Stretch::None;
                    image->Tag = ImageType::Thumbnail;

                    // Create an initial CompositeTransform for the item
                    CompositeTransform^ xform = ref new CompositeTransform();
                    xform->TranslateX = (displayBorder->ActualWidth - bitmap->PixelWidth) / 2;
                    xform->TranslateY = (displayBorder->ActualHeight - bitmap->PixelHeight) / 2;

                    // randomize it
                    xform->TranslateX += rand() % 256 - 128;
                    xform->TranslateY += rand() % 256 - 128;

                    // Create the ManipulableContentControl for the Image
                    ManipulableContentControl^ manipulableControl = ref new ManipulableContentControl(xform);
                    manipulableControl->Content = image;
                    manipulableControl->Tag = storageFile;
                    manipulableControl->ManipulationStarted += ref new ManipulationStartedEventHandler(this, &MainPage::OnManipulableControlManipulationStarted);

                    // Put it in the Grid
                    displayGrid->Children->Append(manipulableControl);
                }
            });
        }
    });
}

void MainPage::OnManipulableControlManipulationStarted(Object^ sender, ManipulationStartedRoutedEventArgs^ args)
{
    ManipulableContentControl^ manipulableControl = dynamic_cast<ManipulableContentControl^>(sender);
    Image^ image = dynamic_cast<Image^>(manipulableControl->Content);

    if ((ImageType)image->Tag == ImageType::Thumbnail)
    {
        // Set tag to transitioning
        image->Tag = ImageType::Transitioning;

        // Load the actual bitmap file
        StorageFile^ storageFile = dynamic_cast<StorageFile^>(manipulableControl->Tag);
        task<WriteableBitmap^> loadBitmapTask = create_task(LoadBitmapAsync(storageFile));
        loadBitmapTask.then([image](WriteableBitmap^ newBitmap)
        {
            if (newBitmap != nullptr)
            {
                // Get the thumbnail from the Image element
                WriteableBitmap^ oldBitmap = dynamic_cast<WriteableBitmap^>(image->Source);

                // Find a ScaleTransform between old and new
                double scale = 1;

                if (oldBitmap->PixelWidth > oldBitmap->PixelHeight)
                    scale = (double)oldBitmap->PixelWidth / newBitmap->PixelWidth;
                else
                    scale = (double)oldBitmap->PixelHeight / newBitmap->PixelHeight;

                // Set properties on the Image element
                image->Source = newBitmap;
                ScaleTransform^ scaleTransform = ref new ScaleTransform();
                scaleTransform->ScaleX = scale;
                scaleTransform->ScaleY = scale;
                image->RenderTransform = scaleTransform;
            }
            image->Tag = ImageType::Full;
        });
    }
}

task<WriteableBitmap^> MainPage::LoadBitmapAsync(StorageFile^ storageFile)
{
    return task<IRandomAccessStreamWithContentType^> (storageFile->OpenReadAsync()).
        then([this](IRandomAccessStreamWithContentType^ stream)
    {
        return LoadBitmapAsync(stream);
    });
}

task<WriteableBitmap^> MainPage::LoadBitmapAsync(StorageItemThumbnail^ thumbnail)
{
    return LoadBitmapAsync(dynamic_cast<IRandomAccessStream^>(thumbnail));
}

task<WriteableBitmap^> MainPage::LoadBitmapAsync(IRandomAccessStream^ stream)
{
    return task<BitmapDecoder^> (BitmapDecoder::CreateAsync(stream)).
    then([](task<BitmapDecoder^> thisTask)
    {
        BitmapDecoder^ decoder = nullptr;

        // raises an exception but causes task to return nullptr
        decoder = thisTask.get();

        // Get the first frame
        return decoder->GetFrameAsync(0);
    }).
    then([this](task<BitmapFrame^> thisTask)
    {
        BitmapFrame^ bitmapFrame = thisTask.get();
        return this->CreateBitmapAsync(bitmapFrame);
    }).
    then([] (WriteableBitmap^ bitmap)
    {
        return bitmap;
    });
}

task<WriteableBitmap^> MainPage::CreateBitmapAsync(BitmapFrame^ bitmapFrame)
{
    int width = bitmapFrame->PixelWidth;
    int height = bitmapFrame->PixelHeight;

    return task<PixelDataProvider^> (bitmapFrame->GetPixelDataAsync(BitmapPixelFormat::Bgra8,
                                                                    BitmapAlphaMode::Premultiplied,
                                                                    ref new BitmapTransform(),
                                                                    ExifOrientationMode::RespectExifOrientation,
                                                                    ColorManagementMode::ColorManageToSRgb)).
        then([width, height](PixelDataProvider^ pixelDataProvider)
        {
            Array<byte>^ filePixels = pixelDataProvider->DetachPixelData();

            // Create WriteableBitmap and set the pixels
            WriteableBitmap^ bitmap = ref new WriteableBitmap(width, height);

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

            // Invalidate the WriteableBitmap and return it
            bitmap->Invalidate();
            return bitmap;
        });
}

