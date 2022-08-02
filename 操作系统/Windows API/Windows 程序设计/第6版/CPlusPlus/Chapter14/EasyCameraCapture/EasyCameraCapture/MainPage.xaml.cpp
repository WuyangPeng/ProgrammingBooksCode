//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace EasyCameraCapture;

using namespace Concurrency;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Media::Capture;
using namespace Windows::Storage;
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
}

void MainPage::OnButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    CameraCaptureUI^ cameraCap = ref new CameraCaptureUI();
    task<StorageFile^> captureFileTask = create_task(cameraCap->CaptureFileAsync(CameraCaptureUIMode::Photo));
    captureFileTask.then([this] (StorageFile^ storageFile)
    {
        if (storageFile != nullptr)
        {
            task<IRandomAccessStreamWithContentType^> openReadTask = create_task(storageFile->OpenReadAsync());
            openReadTask.then([this] (IRandomAccessStreamWithContentType^ stream)
            {
                BitmapImage^ bitmap = ref new BitmapImage();
                image->Source = bitmap;
                task<void> setSourceTask = create_task(bitmap->SetSourceAsync(stream));
                setSourceTask.then([] () 
                {
                });
            });
        }
    });
}
