//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"                // includes ppltasks.h
#include "MainPage.xaml.h"

using namespace QuickNotes;

using namespace Concurrency;
using namespace Platform;
using namespace Windows::ApplicationModel;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Storage;
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
    Loaded += ref new RoutedEventHandler(this, &MainPage::OnLoaded);
    Application::Current->Suspending += ref new SuspendingEventHandler(this, &MainPage::OnAppSuspending);
}

void MainPage::OnLoaded(Object^ sender, RoutedEventArgs^ args)
{
    StorageFolder^ localFolder = ApplicationData::Current->LocalFolder;
    task<StorageFile^> createFileTask = create_task(localFolder->CreateFileAsync("QuickNotes.txt",
                                                                                 CreationCollisionOption::OpenIfExists));
    createFileTask.then([this] (StorageFile^ storageFile)
    {
        task<String^> readTextTask = create_task(FileIO::ReadTextAsync(storageFile));
        readTextTask.then([this] (String^ text)
        {
            txtbox->Text = text;
            txtbox->SelectionStart = txtbox->Text->Length();
            txtbox->Focus(Windows::UI::Xaml::FocusState::Programmatic);
        });
    });
}

void MainPage::OnAppSuspending(Object^ sender, SuspendingEventArgs^ args)
{
    SuspendingDeferral^ deferral = args->SuspendingOperation->GetDeferral();

    task<void> writeTextTask = create_task(PathIO::WriteTextAsync("ms-appdata:///local/QuickNotes.txt", txtbox->Text));
    writeTextTask.then([deferral] () 
    {
        deferral->Complete();
    });
}

