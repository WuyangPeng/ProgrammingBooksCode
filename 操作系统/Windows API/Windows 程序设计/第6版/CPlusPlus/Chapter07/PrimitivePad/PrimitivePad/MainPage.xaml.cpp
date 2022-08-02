//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"                        // includes ppltasks.h
#include "MainPage.xaml.h"

using namespace PrimitivePad;

using namespace Concurrency;
using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;
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
    InitializeComponent();

    Loaded += ref new RoutedEventHandler([this](Object^ sender, RoutedEventArgs^ args)
    {
        ApplicationDataContainer^ appData = ApplicationData::Current->LocalSettings;

        if (appData->Values->HasKey("TextWrapping"))
            txtbox->TextWrapping = (TextWrapping)(int)appData->Values->Lookup("TextWrapping");

        wrapButton->IsChecked = txtbox->TextWrapping == TextWrapping::Wrap;
        wrapButton->Content = wrapButton->IsChecked->Value ? "Wrap" : "No Wrap";

        txtbox->Focus(Windows::UI::Xaml::FocusState::Programmatic);
    });
}

void MainPage::OnFileOpenButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    FileOpenPicker^ picker = ref new FileOpenPicker();
    picker->FileTypeFilter->Append(".txt");
    task<StorageFile^> pickSingleFileTask = create_task(picker->PickSingleFileAsync());
    pickSingleFileTask.then([this] (StorageFile^ storageFile)
    {
        // If user presses Cancel, result is null
        if (storageFile != nullptr)
        {
            task<IRandomAccessStreamWithContentType^> openReadTask = create_task(storageFile->OpenReadAsync());
            openReadTask.then([this] (IRandomAccessStreamWithContentType^ stream)
            {
                DataReader^ dataReader = ref new DataReader(stream);
                unsigned int length = (unsigned int)stream->Size;
                task<size_t> loadReaderTask = create_task(dataReader->LoadAsync(length));
                loadReaderTask.then([this, dataReader] (size_t length)
                {
                    txtbox->Text = dataReader->ReadString(length);
                });
            });
        }
    });
}

void MainPage::OnFileSaveAsButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    FileSavePicker^ picker = ref new FileSavePicker();
    picker->DefaultFileExtension = ".txt";
    picker->FileTypeChoices->Insert("Text", ref new Vector<String^>(1, ".txt"));
    task<StorageFile^> pickSaveFileTask = create_task(picker->PickSaveFileAsync());
    pickSaveFileTask.then([this] (StorageFile^ storageFile)
    {
        // If user presses Cancel, result is null
        if (storageFile != nullptr)
        {
            task<IRandomAccessStream^> openWriteTask = create_task(storageFile->OpenAsync(FileAccessMode::ReadWrite));
            openWriteTask.then([this] (IRandomAccessStream^ stream)
            {
                DataWriter^ dataWriter = ref new DataWriter(stream);
                dataWriter->WriteString(txtbox->Text);
                task<size_t> storeTask = create_task(dataWriter->StoreAsync());
                storeTask.then([] (size_t) {});
            });
        }
    });
}

void MainPage::OnWrapButtonChecked(Object^ sender, RoutedEventArgs^ args)
{
    bool isChecked = wrapButton->IsChecked->Value;
    txtbox->TextWrapping = isChecked ? TextWrapping::Wrap : TextWrapping::NoWrap;
    wrapButton->Content = isChecked ? "Wrap" : "No Wrap";
    ApplicationData::Current->LocalSettings->Values->Insert("TextWrapping", (int)txtbox->TextWrapping);
}
