//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace RichTextEditor;

using namespace Concurrency;
using namespace Microsoft::WRL;
using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::ApplicationModel;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;
using namespace Windows::Storage::Streams;
using namespace Windows::UI::Popups;
using namespace Windows::UI::Text;
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
    try
    {
        // Get font families from DirectWrite
        fontFamilyComboBox->ItemsSource = GetFontFamilies();
    }
    catch (Exception^)
    {
        // Ignore exceptions here
    }

    // Load current document
    StorageFolder^ localFolder = ApplicationData::Current->LocalFolder;
    task<StorageFile^> createFileTask = create_task(localFolder->CreateFileAsync("RichTextEditor.rtf", CreationCollisionOption::OpenIfExists));
    createFileTask.then([this] (StorageFile^ storageFile)
    {
        task<IRandomAccessStream^> openTask = create_task(storageFile->OpenAsync(FileAccessMode::Read));
        openTask.then([this] (task<IRandomAccessStream^> thisTask)
        {
            try
            {
                IRandomAccessStream^ stream = thisTask.get();
                richEditBox->Document->LoadFromStream(TextSetOptions::FormatRtf, stream);
            }
            catch (Exception^)
            {
                // Ignore exceptions here
            }

            // Load selection settings
            IPropertySet^ propertySet = ApplicationData::Current->LocalSettings->Values;

            if (propertySet->HasKey("SelectionStart"))
                richEditBox->Document->Selection->StartPosition = (int)propertySet->Lookup("SelectionStart");

            if (propertySet->HasKey("SelectionEnd"))
                richEditBox->Document->Selection->EndPosition = (int)propertySet->Lookup("SelectionEnd");
        });
    });
}

Vector<String^>^ MainPage::GetFontFamilies()
{
    ComPtr<IDWriteFactory> pWriteFactory;
    HRESULT hresult = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
                                          __uuidof(IDWriteFactory),
                                          &pWriteFactory);
    if (!SUCCEEDED(hresult))
        throw ref new COMException(hresult, "DWriteCreateFactory failure");

    ComPtr<IDWriteFontCollection> pWriteFontCollection;
    hresult = pWriteFactory->GetSystemFontCollection(&pWriteFontCollection, true);

    if (!SUCCEEDED(hresult))
        throw ref new COMException(hresult, "GetSystemFontCollection failure");

    unsigned int count = pWriteFontCollection->GetFontFamilyCount();
    Vector<String^>^ fonts = ref new Vector<String^>();

    for (unsigned int i = 0; i < count; i++)
    {
        IDWriteFontFamily* pWriteFontFamily;
        hresult = pWriteFontCollection->GetFontFamily(i, &pWriteFontFamily);

        if (!SUCCEEDED(hresult))
            throw ref new COMException(hresult, "GetFontFamily failure");

        IDWriteLocalizedStrings* pWriteFamilyNames;
        hresult = pWriteFontFamily->GetFamilyNames(&pWriteFamilyNames);

        if (!SUCCEEDED(hresult))
            throw ref new COMException(hresult, "GetFamilyNames failure");

        unsigned int index = 0;
        BOOL exists;
        hresult = pWriteFamilyNames->FindLocaleName(L"en-us", &index, &exists);

        if (!SUCCEEDED(hresult))
            throw ref new COMException(hresult, "FindLocaleName failure");

        if (exists)
        {
            unsigned int length = 0;
            hresult = pWriteFamilyNames->GetStringLength(index, &length);

            if (!SUCCEEDED(hresult))
                throw ref new COMException(hresult, "GetStringLength failure");

            wchar_t* str = new (std::nothrow) wchar_t[length + 1];
            if (str == nullptr)
                throw ref new OutOfMemoryException("Out of memory on allocation for GetString");

            hresult = pWriteFamilyNames->GetString(index, str, length + 1);

            if (!SUCCEEDED(hresult))
                throw ref new COMException(hresult, "GetString failure");

            String^ string = ref new String(str);
            delete[] str;
            fonts->Append(string);

            pWriteFamilyNames->Release();
            pWriteFontFamily->Release();
        }
    }

    // Sort font families alphabetically
    std::sort(begin(fonts), end(fonts));

    return fonts;
}

void MainPage::OnAppSuspending(Object^ sender, SuspendingEventArgs^ args)
{
    std::shared_ptr<SuspendingDeferral^> pDeferral = 
        std::make_shared<SuspendingDeferral^>(args->SuspendingOperation->GetDeferral());

    // Save current document
    StorageFolder^ localFolder = ApplicationData::Current->LocalFolder;
    task<StorageFile^> createFileTask = create_task(localFolder->CreateFileAsync("RichTextEditor.rtf", CreationCollisionOption::ReplaceExisting));
    createFileTask.then([this, pDeferral] (StorageFile^ storageFile)
    {
        task<IRandomAccessStream^> openTask = create_task(storageFile->OpenAsync(FileAccessMode::ReadWrite));
        openTask.then([this, pDeferral] (task<IRandomAccessStream^> thisTask)
        {
            try
            {
                IRandomAccessStream^ stream = thisTask.get();
                richEditBox->Document->SaveToStream(TextGetOptions::FormatRtf, stream);
            }
            catch (Exception^)
            {
                // Ignore exceptions here
            }

            // Save selection settings
            IPropertySet^ propertySet = ApplicationData::Current->LocalSettings->Values;
            propertySet->Insert("SelectionStart", richEditBox->Document->Selection->StartPosition);
            propertySet->Insert("SelectionEnd", richEditBox->Document->Selection->EndPosition);

            SuspendingDeferral^ deferral = *pDeferral.get();
            deferral->Complete();
        });
    });
}

void MainPage::OnTopAppBarOpened(Platform::Object^ sender, Platform::Object^ args)
{
    // Get the character formatting at the current selection
    ITextCharacterFormat^ charFormat = richEditBox->Document->Selection->CharacterFormat;

    // Set the CheckBox app bar buttons
    boldAppBarCheckBox->IsChecked = charFormat->Bold == FormatEffect::On;
    italicAppBarCheckBox->IsChecked = charFormat->Italic == FormatEffect::On;
    underlineAppBarCheckBox->IsChecked = charFormat->Underline == UnderlineType::Single;

    // Set the two ComboBox's
    fontSizeComboBox->SelectedItem = (int)charFormat->Size;
    fontFamilyComboBox->SelectedItem = charFormat->Name;

    // Get the paragraph alignment and set the RadioButton's
    ParagraphAlignment paragraphAlign = richEditBox->Document->Selection->ParagraphFormat->Alignment;
    alignLeftAppBarRadioButton->IsChecked = paragraphAlign == ParagraphAlignment::Left;
    alignCenterAppBarRadioButton->IsChecked = paragraphAlign == ParagraphAlignment::Center;
    alignRightAppBarRadioButton->IsChecked = paragraphAlign == ParagraphAlignment::Right;
}

void MainPage::OnBoldAppBarCheckBoxChecked(Object^ sender, RoutedEventArgs^ args)
{
    richEditBox->Document->Selection->CharacterFormat->Bold =
        dynamic_cast<CheckBox^>(sender)->IsChecked->Value ? FormatEffect::On : FormatEffect::Off;
}

void MainPage::OnItalicAppBarCheckBoxChecked(Object^ sender, RoutedEventArgs^ args)
{
    richEditBox->Document->Selection->CharacterFormat->Italic =
        dynamic_cast<CheckBox^>(sender)->IsChecked->Value ? FormatEffect::On : FormatEffect::Off;
}

void MainPage::OnUnderlineAppBarCheckBoxChecked(Object^ sender, RoutedEventArgs^ args)
{
    richEditBox->Document->Selection->CharacterFormat->Underline =
        dynamic_cast<CheckBox^>(sender)->IsChecked->Value ? UnderlineType::Single : UnderlineType::None;
}

void MainPage::OnFontSizeComboBoxSelectionChanged(Object^ sender, SelectionChangedEventArgs^ args)
{
    ComboBox^ comboBox = dynamic_cast<ComboBox^>(sender);
    if (comboBox->SelectedItem != nullptr)
    {
        richEditBox->Document->Selection->CharacterFormat->Size = float((int)comboBox->SelectedItem);
    }
}

void MainPage::OnFontFamilyComboBoxSelectionChanged(Object^ sender, SelectionChangedEventArgs^ args)
{
    ComboBox^ comboBox = dynamic_cast<ComboBox^>(sender);
    if (comboBox->SelectedItem != nullptr)
    {
        richEditBox->Document->Selection->CharacterFormat->Name = dynamic_cast<String^>(comboBox->SelectedItem);
    }
}

void MainPage::OnAlignAppBarRadioButtonChecked(Object^ sender, RoutedEventArgs^ args)
{
    RadioButton^ radioButton = dynamic_cast<RadioButton^>(sender);
    ParagraphAlignment paragraphAlign = ParagraphAlignment::Undefined;

    if (radioButton == alignLeftAppBarRadioButton)
        paragraphAlign = ParagraphAlignment::Left;

    else if (radioButton == alignCenterAppBarRadioButton)
        paragraphAlign = ParagraphAlignment::Center;

    else if (radioButton == alignRightAppBarRadioButton)
        paragraphAlign = ParagraphAlignment::Right;

    richEditBox->Document->Selection->ParagraphFormat->Alignment = paragraphAlign;
}

void MainPage::OnOpenAppBarButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    FileOpenPicker^ picker = ref new FileOpenPicker();
    picker->FileTypeFilter->Append(".txt");
    picker->FileTypeFilter->Append(".rtf");

    task<StorageFile^> pickOpenFileTask = create_task(picker->PickSingleFileAsync());
    pickOpenFileTask.then([this] (StorageFile^ storageFile)
    {
        // If user presses Cancel, result is nullptrt
        if (storageFile != nullptr)
        {
            TextSetOptions textOptions = storageFile->ContentType != "text/plain" ? TextSetOptions::FormatRtf : TextSetOptions::None;
            task<IRandomAccessStream^> openTask = create_task(storageFile->OpenAsync(FileAccessMode::Read));
            openTask.then([this, textOptions] (task<IRandomAccessStream^> thisTask)
            {
                String^ message = nullptr;

                try
                {
                    IRandomAccessStream^ stream = thisTask.get();
                    richEditBox->Document->LoadFromStream(textOptions, stream);
                }
                catch (Exception^ exc)
                {
                    message = exc->Message;
                }

                if (message != nullptr)
                {
                    MessageDialog^ msgdlg = ref new MessageDialog("The file could not be opened. " +
                                                                  "Windows reports the following error: " +
                                                                  message, "RichTextEditor");
                    task<IUICommand^> messageDialogShowTask = create_task(msgdlg->ShowAsync());
                    messageDialogShowTask.then([] (IUICommand^ uiCommand) {});
                }
            });
        }
    });
}

void MainPage::OnSaveAsAppBarButtonClick(Object^ sender, RoutedEventArgs^ args)
{
    FileSavePicker^ picker = ref new FileSavePicker();
    picker->DefaultFileExtension = ".rtf";
    picker->FileTypeChoices->Insert("Rich Text Document", ref new Vector<String^>(1, ".rtf"));
    picker->FileTypeChoices->Insert("Text Document", ref new Vector<String^>(1, ".txt"));

    task<StorageFile^> pickSaveFileTask = create_task(picker->PickSaveFileAsync());
    pickSaveFileTask.then([this] (StorageFile^ storageFile)
    {
        // If user presses Cancel, result is nullptr
        if (storageFile != nullptr)
        {
            TextGetOptions textOptions = storageFile->ContentType != "text/plain" ? TextGetOptions::FormatRtf : TextGetOptions::None;
            task<IRandomAccessStream^> openTask = create_task(storageFile->OpenAsync(FileAccessMode::ReadWrite));
            openTask.then([this, textOptions] (task<IRandomAccessStream^> thisTask)
            {
                String^ message = nullptr;

                try
                {
                    IRandomAccessStream^ stream = thisTask.get();
                    richEditBox->Document->SaveToStream(textOptions, stream);
                }
                catch (Exception^ exc)
                {
                    message = exc->Message;
                }

                if (message != nullptr)
                {
                    MessageDialog^ msgdlg = ref new MessageDialog("The file could not be saved. " +
                                                                  "Windows reports the following error: " +
                                                                  message, "RichTextEditor");
                    task<IUICommand^> messageDialogShowTask = create_task(msgdlg->ShowAsync());
                    messageDialogShowTask.then([] (IUICommand^ uiCommand) {});
                }
            });
        }
    });
}
