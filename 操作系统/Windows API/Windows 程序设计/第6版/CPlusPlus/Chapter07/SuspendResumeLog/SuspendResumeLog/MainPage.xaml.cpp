//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"                    // includes ppltasks.h and time.h
#include "MainPage.xaml.h"

using namespace SuspendResumeLog;

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
    Application::Current->Resuming += ref new EventHandler<Object^>(this, &MainPage::OnAppResuming);
}

void MainPage::OnLoaded(Object^ sender, RoutedEventArgs^ args)
{
    // Create or obtain the log file
    StorageFolder^ localFolder = ApplicationData::Current->LocalFolder;
    task<StorageFile^> createFileTask = create_task(localFolder->CreateFileAsync("logfile.txt",
                                                                                 CreationCollisionOption::OpenIfExists));
    createFileTask.then([this] (StorageFile^ storageFile)
    {
        logfile = storageFile;

        // Load the file and display it
        task<String^> readTextTask = create_task(FileIO::ReadTextAsync(logfile));
        readTextTask.then([this] (String^ text)
        {
            txtbox->Text = text;

            // Log the launch
            txtbox->Text += "Launching at " + GetFormattedDateTime() + "\r\n";
            task<void> writeTextTask = create_task(FileIO::WriteTextAsync(logfile, txtbox->Text));
            writeTextTask.then([] () {});
        });
    });
}

void MainPage::OnAppSuspending(Object^ sender, SuspendingEventArgs^ args)
{
    SuspendingDeferral^ deferral = args->SuspendingOperation->GetDeferral();

    // Log the suspension
    txtbox->Text += "Suspending at " + GetFormattedDateTime() + "\r\n";
    task<void> writeTextTask = create_task(FileIO::WriteTextAsync(logfile, txtbox->Text));
    writeTextTask.then([deferral] () 
    {
        deferral->Complete();
    });
}

void MainPage::OnAppResuming(Object^ sender, Object^ args)
{
    // Log the resumption
    txtbox->Text += "Resuming at " + GetFormattedDateTime() + "\r\n";
    task<void> writeTextTask = create_task(FileIO::WriteTextAsync(logfile, txtbox->Text));
    writeTextTask.then([] () {});
}

String^ MainPage::GetFormattedDateTime()
{
  time_t intTime;
  time(&intTime);

  struct tm timeStruct;
  localtime_s(&timeStruct, &intTime);

  wchar_t str[64];
  wcsftime (str, 64, L"%x %X", &timeStruct);
  return ref new String(str);
}


