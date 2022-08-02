//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace PrivateFonts;

using namespace Concurrency;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Storage;
using namespace Windows::Storage::Streams;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

MainPage::MainPage()
{
    StorageFolder^ localFolder = ApplicationData::Current->LocalFolder;
    task<StorageFolder^> getFolderTask = create_task(localFolder->GetFolderAsync("Fonts"));
    getFolderTask.then([this] (task<StorageFolder^> thisTask)
    {
        bool folderExists = false;

        try
        {
            StorageFolder^ fontsFolder = thisTask.get();
            folderExists = true;
        }
        catch (Exception^)
        {
        }

        if (folderExists)
        {
            InitializeComponent();
        }
        else
        {
            StorageFolder^ localFolder = ApplicationData::Current->LocalFolder;
            task<StorageFolder^> createFolderTask = create_task(localFolder->CreateFolderAsync("Fonts"));
            createFolderTask.then([this](StorageFolder^ fontsFolder)
            {
                std::array<task<void>, 8> tasks = 
                {
                    create_task(TransferFontFile(fontsFolder, "Kooten.ttf")),
                    create_task(TransferFontFile(fontsFolder, "Linds.ttf")),
                    create_task(TransferFontFile(fontsFolder, "Miramo.ttf")),
                    create_task(TransferFontFile(fontsFolder, "Miramob.ttf")),
                    create_task(TransferFontFile(fontsFolder, "Peric.ttf")),
                    create_task(TransferFontFile(fontsFolder, "Pericl.ttf")),
                    create_task(TransferFontFile(fontsFolder, "Pesca.ttf")),
                    create_task(TransferFontFile(fontsFolder, "Pescab.ttf"))
                };
                when_all(begin(tasks), end(tasks)).then([this] ()
                {
                    InitializeComponent();
                });
            });
        }
    });
}

task<void> MainPage::TransferFontFile(StorageFolder^ fontsFolder, String^ filename)
{
    // Copy from application content to IBuffer
    String^ uri = "ms-appx:///Fonts/" + filename;
    task<IBuffer^> readBufferTask = create_task(PathIO::ReadBufferAsync(uri));
    return readBufferTask.then([fontsFolder, filename] (IBuffer^ buffer)
    {
        // Copy from IBuffer to local storage
        task<StorageFile^> createFileTask = create_task(fontsFolder->CreateFileAsync(filename));
        return createFileTask.then([buffer] (StorageFile^ fontFile)
        {
            task<void> writeBufferTask = create_task(FileIO::WriteBufferAsync(fontFile, buffer));
            return writeBufferTask.then([] () { });
        });
    });
}


