//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace AppBarPad;

using namespace Concurrency;
using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::ApplicationModel;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;
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

    Loaded += ref new RoutedEventHandler([this] (Object^, RoutedEventArgs^)
    {
        // Get local settings object
        ApplicationDataContainer^ appData = ApplicationData::Current->LocalSettings;

        // Load TextBox settings
        if (appData->Values->HasKey("TextWrapping"))
            txtbox->TextWrapping = (TextWrapping)(int)appData->Values->Lookup("TextWrapping");

        if (appData->Values->HasKey("FontSize"))
            txtbox->FontSize = (double)appData->Values->Lookup("FontSize");

        // Load TextBox content
        StorageFolder^ localFolder = ApplicationData::Current->LocalFolder;
        task<StorageFile^> createFileTask = create_task(localFolder->CreateFileAsync("AppBarPad.txt",
                                                                CreationCollisionOption::OpenIfExists));
        createFileTask.then([this] (StorageFile^ storageFile)
        {
            task<String^> readTextTask = create_task(FileIO::ReadTextAsync(storageFile));
            readTextTask.then([this] (String^ text)
            {
                txtbox->Text = text;

                // Enable the TextBox and give it input focus
                txtbox->IsEnabled = true;
                txtbox->Focus(Windows::UI::Xaml::FocusState::Programmatic);
            });
        });
    });

    Application::Current->Suspending += ref new SuspendingEventHandler([this] (Object^, SuspendingEventArgs^ args)
    {
        // Get local settings object
        ApplicationDataContainer^ appData = ApplicationData::Current->LocalSettings;

        // Save TextBox settings
        appData->Values->Insert("TextWrapping", (int)txtbox->TextWrapping);
        appData->Values->Insert("FontSize", txtbox->FontSize);

        // Save TextBox content
        SuspendingDeferral^ deferral = args->SuspendingOperation->GetDeferral();
        task<void> writeTextTask = create_task(PathIO::WriteTextAsync("ms-appdata:///local/AppBarPad.txt", txtbox->Text));
        writeTextTask.then([deferral] ()
        {
            deferral->Complete();
        });
    });
}

void MainPage::OnFontIncreaseAppBarButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    ChangeFontSize(1.1);
}

void MainPage::OnFontDecreaseAppBarButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    ChangeFontSize(1 / 1.1);
}

void MainPage::ChangeFontSize(double multiplier)
{
    txtbox->FontSize *= multiplier;
}

void MainPage::OnWrapOptionAppBarButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    Button^ btn = dynamic_cast<Button^>(sender);

    // Create dialog
    WrapOptionsDialog^ wrapOptionsDialog = ref new WrapOptionsDialog();
    wrapOptionsDialog->TextWrapping = txtbox->TextWrapping;

    // Bind dialog to TextBox
    Binding^ binding = ref new Binding();
    binding->Source = wrapOptionsDialog;
    binding->Path = ref new PropertyPath("TextWrapping");
    binding->Mode = BindingMode::TwoWay;
    txtbox->SetBinding(TextBox::TextWrappingProperty, binding);

    Popup^ popup = ref new Popup();
    popup->Child = wrapOptionsDialog;
    popup->IsLightDismissEnabled = true;

    // Adjust location based on current size
    wrapOptionsDialog->SizeChanged += ref new SizeChangedEventHandler(
        [this, popup, btn] (Object^ sender, SizeChangedEventArgs^ args)
        {
            // Get Button location relative to screen
            Point pt = btn->TransformToVisual(nullptr)->TransformPoint(Point(float(btn->ActualWidth) / 2,
                                                                             float(btn->ActualHeight) / 2));

            popup->HorizontalOffset = pt.X - args->NewSize.Width / 2;
            popup->VerticalOffset = this->ActualHeight - args->NewSize.Height
                                                       - this->BottomAppBar->ActualHeight - 48;
        });

    // Open the popup
    popup->IsOpen = true;
}

void MainPage::OnOpenAppBarButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    FileOpenPicker^ picker = ref new FileOpenPicker();
    picker->FileTypeFilter->Append(".txt");

    task<StorageFile^> pickSingleFileTask(picker->PickSingleFileAsync());
    pickSingleFileTask.then([this](StorageFile^ storageFile)
    {
        if (storageFile != nullptr)
        {
            task<String^> readTextTask(FileIO::ReadTextAsync(storageFile));
            readTextTask.then([this](String^ text)
            {
                txtbox->Text = text;
            });
        }
    });
}

void MainPage::OnSaveAsAppBarButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    FileSavePicker^ picker = ref new FileSavePicker();
    picker->DefaultFileExtension = ".txt";
    picker->FileTypeChoices->Insert("Text", ref new Vector<String^>(1, ".txt"));

    task<StorageFile^> pickSaveFileTask(picker->PickSaveFileAsync());
    pickSaveFileTask.then([this](StorageFile^ storageFile)
    {
        if (storageFile != nullptr)
        {
            task<void> writeTextTask(FileIO::WriteTextAsync(storageFile, txtbox->Text));
            writeTextTask.then([] () {});
        }
    });
}

