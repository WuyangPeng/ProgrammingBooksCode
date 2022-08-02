//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace XamlCruncher;

using namespace Concurrency;
using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::ApplicationModel;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Globalization::Fonts;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;
using namespace Windows::UI;
using namespace Windows::UI::Core;
using namespace Windows::UI::Popups;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::Xaml::Markup;

MainPage::MainPage()
{
    InitializeComponent();

    loadedStorageFile = nullptr;

    // Set brushes
    textBlockBrush = dynamic_cast<Brush^>(this->Resources->Lookup("ApplicationForegroundThemeBrush"));
    textBoxBrush = dynamic_cast<Brush^>(this->Resources->Lookup("TextBoxForegroundThemeBrush"));
    errorBrush = ref new SolidColorBrush(Colors::Red);

    // Why aren't these set in the generated C++ files?
    editBox = dynamic_cast<TabbableTextBox^>(splitContainer->Child1);
    resultContainer = dynamic_cast<RulerContainer^>(splitContainer->Child2);

    // Set a fixed-pitch font for the TextBox
    Windows::Globalization::Language^ language = ref new Windows::Globalization::Language(Windows::Globalization::Language::CurrentInputMethodLanguageTag);
    LanguageFontGroup^ languageFontGroup = ref new LanguageFontGroup(language->LanguageTag);
    LanguageFont^ languageFont = languageFontGroup->FixedWidthTextFont;
    editBox->FontFamily = ref new Windows::UI::Xaml::Media::FontFamily(languageFont->FontFamily);

    Loaded += ref new RoutedEventHandler(this, &MainPage::OnLoaded);
    Application::Current->Suspending += ref new SuspendingEventHandler(this, &MainPage::OnApplicationSuspending);
}

void MainPage::OnLoaded(Object^ sender, RoutedEventArgs^ args)
{
    // Load AppSettings and set to DataContext
    appSettings = ref new AppSettings();
    this->DataContext = appSettings;

    // Load any file that may have been saved
    StorageFolder^ localFolder = ApplicationData::Current->LocalFolder;
    task<StorageFile^> createFileTask = create_task(localFolder->CreateFileAsync("XamlCruncher.xaml",
                                                                                 CreationCollisionOption::OpenIfExists));
    createFileTask.then([this](StorageFile^ storageFile)
    {
        task<String^> readTextTask = create_task(FileIO::ReadTextAsync(storageFile));
        readTextTask.then([this](String^ text)
        {
            if (text == nullptr || text->Length() == 0)
            {
                task<void> setDefaultXamlTask = MainPage::SetDefaultXamlFile();
                setDefaultXamlTask.then([this]
                {
                    FinishInitialization();
                }, task_continuation_context::use_current());
            }
            else
            {
                editBox->Text = text;
                FinishInitialization();
            }
        });
    });
}

void MainPage::FinishInitialization()
{
    ParseText();
    editBox->Focus(Windows::UI::Xaml::FocusState::Keyboard);
    DisplayLineAndColumn();

    Application::Current->UnhandledException += ref new UnhandledExceptionEventHandler(
        [this](Object^ sender, UnhandledExceptionEventArgs^ args)
        {
            SetErrorText(args->Message);
            args->Handled = true;
        });
}

void MainPage::OnApplicationSuspending(Object^ sender, SuspendingEventArgs^ args)
{
    // Save application settings
    appSettings->Save();

    // Save text content
    SuspendingDeferral^ deferral = args->SuspendingOperation->GetDeferral();
    task<void> writeTextTask = create_task(PathIO::WriteTextAsync("ms-appdata:///local/XamlCruncher.xaml", editBox->Text));
    writeTextTask.then([this, deferral]()
    {
        deferral->Complete();
    });
}

task<void> MainPage::SetDefaultXamlFile()
{
     editBox->Text = 
        "<Page xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\"\r\n" +
        "      xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\">\r\n\r\n" +
        "    <TextBlock Text=\"Hello, Windows 8!\"\r\n" +
        "               FontSize=\"48\" />\r\n\r\n" +
        "</Page>";

    editBox->IsModified = false;
    loadedStorageFile = nullptr;
    filenameText->Text = "";

    return task<void>([this]{});
}

void MainPage::OnRefreshAppBarButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    ParseText();
    this->BottomAppBar->IsOpen = false;
}

void MainPage::OnSettingsAppBarButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    SettingsDialog^ settingsDialog = ref new SettingsDialog();
    settingsDialog->DataContext = appSettings;

    Popup^ popup = ref new Popup();
    popup->Child = settingsDialog;
    popup->IsLightDismissEnabled = true;

    // Adjust location based on current size
    settingsDialog->SizeChanged += ref new SizeChangedEventHandler(
        [this,settingsDialog,popup] (Object^ dialogSender, SizeChangedEventArgs^ dialogArgs)
        {
            popup->VerticalOffset = this->ActualHeight - settingsDialog->ActualHeight
                                                       - this->BottomAppBar->ActualHeight - 24;
            popup->HorizontalOffset = 24;
        });

    popup->Closed += ref new EventHandler<Object^>([this] (Object^, Object^)
        {
            this->BottomAppBar->IsOpen = false;        
        });
    popup->IsOpen = true;
}

void MainPage::OnAddAppBarButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    Button^ button = dynamic_cast<Button^>(sender);
    button->IsEnabled = false;

    task<void> checkIfOkToTrashTask(MainPage::CheckIfOkToTrashFile(&MainPage::SetDefaultXamlFile));
    checkIfOkToTrashTask.then([this,button]()
    {
        bool x = this->Dispatcher->HasThreadAccess;

        button->IsEnabled = true;
        this->BottomAppBar->IsOpen = false;
    }, task_continuation_context::use_current());
}

void MainPage::OnOpenAppBarButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    Button^ button = dynamic_cast<Button^>(sender);
    button->IsEnabled = false;

    task<void> checkIfOkToTrashTask(MainPage::CheckIfOkToTrashFile(&MainPage::LoadFileFromOpenPicker));
    checkIfOkToTrashTask.then([this,button]()
    {
        button->IsEnabled = true;
        this->BottomAppBar->IsOpen = false;
    }, task_continuation_context::use_current());
}

task<void> MainPage::CheckIfOkToTrashFile(task<void> (MainPage::*commandAction)(void))
{
    if (!editBox->IsModified)
    {
        return (this->*commandAction)();
    }

    String^ message = "Do you want to save changes to " +
                      (loadedStorageFile == nullptr ? "(untitled)" : loadedStorageFile->Name) +
                      "?";

    MessageDialog^ msgdlg = ref new MessageDialog(message, "XAML Cruncher");
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

        if (loadedStorageFile == nullptr)
        {
            task<StorageFile^> getFileFromSavePickerTask(MainPage::GetFileFromSavePicker());
            return getFileFromSavePickerTask.then([this,commandAction](StorageFile^ storageFile)
            {
                if (storageFile == nullptr)
                    return task<void>([]{});;

                loadedStorageFile = storageFile;

                task<void> saveXamlToFileTask(MainPage::SaveXamlToFile(loadedStorageFile));
                return saveXamlToFileTask.then([this,commandAction]()
                {
                    return (this->*commandAction)();
                });
            });
        }
    
        task<void> saveXamlToFileTask(MainPage::SaveXamlToFile(loadedStorageFile));
        return saveXamlToFileTask.then([this,commandAction]()
        {
            return (this->*commandAction)();
        });
    });
}

task<void> MainPage::LoadFileFromOpenPicker()
{
    FileOpenPicker^ picker = ref new FileOpenPicker();
    picker->FileTypeFilter->Append(".xaml");

    task<StorageFile^> pickSingleFileTask(picker->PickSingleFileAsync());
    return pickSingleFileTask.then(
        [this](StorageFile^ storageFile)
        {
            if (storageFile == nullptr)
                return;

            task<String^> readTextTask(FileIO::ReadTextAsync(storageFile));
            readTextTask.then([this,storageFile] (task<String^> thisTask)
            {
                Exception^ exception = nullptr;

                try
                {
                    editBox->Text = thisTask.get();
                }
                catch (Exception^ exc)
                {
                    exception = exc;
                }

                if (exception != nullptr)
                {
                    String^ message = "Could not load file " +
                                      storageFile->Name +
                                      ": " +
                                      exception->Message;

                    MessageDialog^ msgdlg = ref new MessageDialog(message, "XAML Cruncher");
                    task<IUICommand^> messageDialogShowTask(msgdlg->ShowAsync());
                    messageDialogShowTask.then([] (IUICommand^ uiCommand) {});
                }
                else
                {
                    editBox->IsModified = false;
                    loadedStorageFile = storageFile;
                    filenameText->Text = loadedStorageFile->Path;
                }
            });
    });
}

void MainPage::OnSaveAsAppBarButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    task<StorageFile^> getFileFromSavePickerTask(MainPage::GetFileFromSavePicker());
    getFileFromSavePickerTask.then([this](StorageFile^ storageFile)
    {
        if (storageFile != nullptr)
        {
            task<void> saveXamlToFileTask(MainPage::SaveXamlToFile(storageFile));
            saveXamlToFileTask.then([this]()
            {
            });
        }
    });
}

void MainPage::OnSaveAppBarButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    if (loadedStorageFile == nullptr)
    {
        MainPage::OnSaveAsAppBarButtonClick(sender, args);
        return;
    }

    Button^ button = dynamic_cast<Button^>(sender);
    button->IsEnabled = false;

    task<void> saveXamlToFileTask(MainPage::SaveXamlToFile(loadedStorageFile));
    saveXamlToFileTask.then([this,button]()
    {
        button->IsEnabled = true;
    });
}

task<StorageFile^> MainPage::GetFileFromSavePicker()
{
    FileSavePicker^ picker = ref new FileSavePicker();
    picker->DefaultFileExtension = ".xaml";
    picker->FileTypeChoices->Insert("XAML", ref new Vector<String^>(1, ".xaml"));
    picker->SuggestedSaveFile = loadedStorageFile;
    task<StorageFile^> pickSaveFileTask(picker->PickSaveFileAsync());
    return pickSaveFileTask;
}

task<void> MainPage::SaveXamlToFile(StorageFile^ storageFile)
{
    loadedStorageFile = storageFile;

    task<void> writeTextTask(FileIO::WriteTextAsync(loadedStorageFile, editBox->Text));
    return writeTextTask.then([this,storageFile] (task<void> thisTask)
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
            String^ message = "Could not save file " +
                              storageFile->Name +
                              ": " +
                              exception->Message;

            MessageDialog^ msgdlg = ref new MessageDialog(message, "XAML Cruncher");
            task<IUICommand^> messageDialogShowTask(msgdlg->ShowAsync());
            messageDialogShowTask.then([] (IUICommand^ uiCommand) {});
        }
        else
        {
            editBox->IsModified = false;
            filenameText->Text = storageFile->Path;
        }
    });
}

// TextBox Events
void MainPage::OnEditBoxSelectionChanged(Object^ sender, RoutedEventArgs^ args)
{
    DisplayLineAndColumn();
}

void MainPage::DisplayLineAndColumn()
{
    int line, col;
    editBox->GetPositionFromIndex(editBox->SelectionStart, &line, &col);
    wchar_t text[24];
    swprintf(text, sizeof(text) / sizeof(text[0]), L"Line %i Col %i", line + 1, col + 1);
    lineColText->Text = ref new String(text);

    if (editBox->SelectionLength > 0)
    {
        editBox->GetPositionFromIndex(editBox->SelectionStart + editBox->SelectionLength - 1, &line, &col);
        swprintf(text, sizeof(text) / sizeof(text[0]), L" - Line %i Col %i", line + 1, col + 1);
        lineColText->Text += ref new String(text);
    }
}

void MainPage::OnEditBoxTextChanged(Object^ sender, TextChangedEventArgs^ args)
{
    if (appSettings->AutoParsing)
        ParseText();
}

void MainPage::ParseText()
{
    Object^ result = nullptr;

    try
    {
        result = XamlReader::Load(editBox->Text);
    }
    catch (Exception^ exc)
    {
        SetErrorText(exc->Message);
        return;
    }

    if (result == nullptr)
    {
        SetErrorText("Null result");
        return;
    }

    UIElement^ element = dynamic_cast<UIElement^>(result);

    if (element != nullptr)
    {
        resultContainer->Child = element;
        SetOkText();
        return;
    }

    SetErrorText("Result is " + result->GetType()->FullName);
}

void MainPage::SetErrorText(String^ text)
{
    SetStatusText(text, errorBrush, errorBrush);
}

void MainPage::SetOkText()
{
    SetStatusText("OK", textBlockBrush, textBoxBrush);
}

void MainPage::SetStatusText(String^ Text, Brush^ statusBrush, Brush^ editBrush)
{
    statusText->Text = Text;
    statusText->Foreground = statusBrush;
    editBox->Foreground = editBrush;
}
