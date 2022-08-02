//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include "FolderItem.h"
#include "ManipulableContentControl.xaml.h"

namespace PhotoScatter
{
    public ref class MainPage sealed
    {
    public:
        MainPage();

    private:
        void OnMainPageLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ args);
        void BuildFolderListBox(Windows::Storage::StorageFolder^ parentStorageFolder, int level);
        void OnFolderListBoxSelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ args);
        void OnManipulableControlManipulationStarted(Platform::Object^ sender, Windows::UI::Xaml::Input::ManipulationStartedRoutedEventArgs^ args);
        Concurrency::task<Windows::UI::Xaml::Media::Imaging::WriteableBitmap^> LoadBitmapAsync(Windows::Storage::StorageFile^ storageFile);
        Concurrency::task<Windows::UI::Xaml::Media::Imaging::WriteableBitmap^> LoadBitmapAsync(Windows::Storage::FileProperties::StorageItemThumbnail^ thumbnail);
        Concurrency::task<Windows::UI::Xaml::Media::Imaging::WriteableBitmap^> LoadBitmapAsync(Windows::Storage::Streams::IRandomAccessStream^ stream);
        Concurrency::task<Windows::UI::Xaml::Media::Imaging::WriteableBitmap^> CreateBitmapAsync(Windows::Graphics::Imaging::BitmapFrame^ bitmapFrame);
    };
}
