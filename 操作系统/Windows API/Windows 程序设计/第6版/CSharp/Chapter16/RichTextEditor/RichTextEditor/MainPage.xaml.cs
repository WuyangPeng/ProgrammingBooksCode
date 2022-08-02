using System;
using System.Collections.Generic;
using Windows.ApplicationModel;
using Windows.Foundation.Collections;
using Windows.Storage;
using Windows.Storage.Pickers;
using Windows.Storage.Streams;
using Windows.UI.Popups;
using Windows.UI.Text;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

using DirectXWrapper;

namespace RichTextEditor
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
            Loaded += OnLoaded;
            Application.Current.Suspending += OnAppSuspending;
        }

        async void OnLoaded(object sender, RoutedEventArgs args)
        {
            // Get fonts from DirectXWrapper library
            WriteFactory writeFactory = new WriteFactory();
            WriteFontCollection writeFontCollection =
                        writeFactory.GetSystemFontCollection();

            int count = writeFontCollection.GetFontFamilyCount();
            string[] fonts = new string[count];

            for (int i = 0; i < count; i++)
            {
                WriteFontFamily writeFontFamily =
                                    writeFontCollection.GetFontFamily(i);

                WriteLocalizedStrings writeLocalizedStrings =
                                    writeFontFamily.GetFamilyNames();
                int index;

                if (writeLocalizedStrings.FindLocaleName("en-us", out index))
                    fonts[i] = writeLocalizedStrings.GetString(index);
                else
                    fonts[i] = writeLocalizedStrings.GetString(0);
            }

            Array.Sort<string>(fonts);
            fontFamilyComboBox.ItemsSource = fonts;

            // Load current document
            StorageFolder localFolder = ApplicationData.Current.LocalFolder;

            try
            {
                StorageFile storageFile = await localFolder.CreateFileAsync("RichTextEditor.rtf",
                                                       CreationCollisionOption.OpenIfExists);
                IRandomAccessStream stream = await storageFile.OpenAsync(FileAccessMode.Read);
                richEditBox.Document.LoadFromStream(TextSetOptions.FormatRtf, stream);
            }
            catch
            {
                // Ignore exceptions here
            }

            // Load selection settings
            IPropertySet propertySet = ApplicationData.Current.LocalSettings.Values;

            if (propertySet.ContainsKey("SelectionStart"))
                richEditBox.Document.Selection.StartPosition = (int)propertySet["SelectionStart"];

            if (propertySet.ContainsKey("SelectionEnd"))
                richEditBox.Document.Selection.EndPosition = (int)propertySet["SelectionEnd"];
        }

        async void OnAppSuspending(object sender, SuspendingEventArgs args)
        {
            SuspendingDeferral deferral = args.SuspendingOperation.GetDeferral();

            // Save current document
            StorageFolder localFolder = ApplicationData.Current.LocalFolder;

            try
            {
                StorageFile storageFile = await localFolder.CreateFileAsync("RichTextEditor.rtf",
                                                       CreationCollisionOption.ReplaceExisting);
                IRandomAccessStream stream = await storageFile.OpenAsync(FileAccessMode.ReadWrite);
                richEditBox.Document.SaveToStream(TextGetOptions.FormatRtf, stream);
            }
            catch
            {
                // Ignore exceptions here
            }

            // Save selection settings
            IPropertySet propertySet = ApplicationData.Current.LocalSettings.Values;
            propertySet["SelectionStart"] = richEditBox.Document.Selection.StartPosition;
            propertySet["SelectionEnd"] = richEditBox.Document.Selection.EndPosition;

            deferral.Complete();
        }

        void OnTopAppBarOpened(object sender, object args)
        {
            // Get the character formatting at the current selection
            ITextCharacterFormat charFormat = richEditBox.Document.Selection.CharacterFormat;

            // Set the CheckBox app bar buttons
            boldAppBarCheckBox.IsChecked = charFormat.Bold == FormatEffect.On;
            italicAppBarCheckBox.IsChecked = charFormat.Italic == FormatEffect.On;
            underlineAppBarCheckBox.IsChecked = charFormat.Underline == UnderlineType.Single;

            // Set the two ComboBox's
            fontSizeComboBox.SelectedItem = (int)charFormat.Size;
            fontFamilyComboBox.SelectedItem = charFormat.Name;

            // Get the paragraph alignment and set the RadioButton's
            ParagraphAlignment paragraphAlign = richEditBox.Document.Selection.ParagraphFormat.Alignment;
            alignLeftAppBarRadioButton.IsChecked = paragraphAlign == ParagraphAlignment.Left;
            alignCenterAppBarRadioButton.IsChecked = paragraphAlign == ParagraphAlignment.Center;
            alignRightAppBarRadioButton.IsChecked = paragraphAlign == ParagraphAlignment.Right;
        }

        void OnBoldAppBarCheckBoxChecked(object sender, RoutedEventArgs args)
        {
            richEditBox.Document.Selection.CharacterFormat.Bold =
                (sender as CheckBox).IsChecked.Value ? FormatEffect.On : FormatEffect.Off;
        }

        void OnItalicAppBarCheckBoxChecked(object sender, RoutedEventArgs args)
        {
            richEditBox.Document.Selection.CharacterFormat.Italic =
                (sender as CheckBox).IsChecked.Value ? FormatEffect.On : FormatEffect.Off;
        }

        void OnUnderlineAppBarCheckBoxChecked(object sender, RoutedEventArgs args)
        {
            richEditBox.Document.Selection.CharacterFormat.Underline =
                (sender as CheckBox).IsChecked.Value ? UnderlineType.Single : UnderlineType.None;
        }

        void OnFontSizeComboBoxSelectionChanged(object sender, SelectionChangedEventArgs args)
        {
            ComboBox comboBox = sender as ComboBox;
            if (comboBox.SelectedItem != null)
            {
                richEditBox.Document.Selection.CharacterFormat.Size = (int)comboBox.SelectedItem;
            }
        }

        void OnFontFamilyComboBoxSelectionChanged(object sender, SelectionChangedEventArgs args)
        {
            ComboBox comboBox = sender as ComboBox;
            if (comboBox.SelectedItem != null)
            {
                richEditBox.Document.Selection.CharacterFormat.Name = (string)comboBox.SelectedItem;
            }
        }

        void OnAlignAppBarRadioButtonChecked(object sender, RoutedEventArgs args)
        {
            ParagraphAlignment paragraphAlign = ParagraphAlignment.Undefined;

            if (sender == alignLeftAppBarRadioButton)
                paragraphAlign = ParagraphAlignment.Left;

            else if (sender == alignCenterAppBarRadioButton)
                paragraphAlign = ParagraphAlignment.Center;

            else if (sender == alignRightAppBarRadioButton)
                paragraphAlign = ParagraphAlignment.Right;

            richEditBox.Document.Selection.ParagraphFormat.Alignment = paragraphAlign;
        }

        async void OnOpenAppBarButtonClick(object sender, RoutedEventArgs args)
        {
            FileOpenPicker picker = new FileOpenPicker();
            picker.FileTypeFilter.Add(".txt");
            picker.FileTypeFilter.Add(".rtf");
            StorageFile storageFile = await picker.PickSingleFileAsync();

            // If user presses Cancel, result is null
            if (storageFile == null)
                return;

            TextSetOptions textOptions = TextSetOptions.None;

            if (storageFile.ContentType != "text/plain")
                textOptions = TextSetOptions.FormatRtf;

            string message = null;

            try
            {
                IRandomAccessStream stream = await storageFile.OpenAsync(FileAccessMode.Read);
                richEditBox.Document.LoadFromStream(textOptions, stream);
            }
            catch (Exception exc)
            {
                message = exc.Message;
            }

            if (message != null)
            {
                MessageDialog msgdlg = new MessageDialog("The file could not be opened. " +
                                                         "Windows reports the following error: " +
                                                         message, "RichTextEditor");
                await msgdlg.ShowAsync();
            }
        }

        async void OnSaveAsAppBarButtonClick(object sender, RoutedEventArgs args)
        {
            FileSavePicker picker = new FileSavePicker();
            picker.DefaultFileExtension = ".rtf";
            picker.FileTypeChoices.Add("Rich Text Document", new List<string> { ".rtf" });
            picker.FileTypeChoices.Add("Text Document", new List<string> { ".txt" });
            StorageFile storageFile = await picker.PickSaveFileAsync();

            // If user presses Cancel, result is null
            if (storageFile == null)
                return;

            TextGetOptions textOptions = TextGetOptions.None;

            if (storageFile.ContentType != "text/plain")
                textOptions = TextGetOptions.FormatRtf;

            string message = null;

            try
            {
                IRandomAccessStream stream = await storageFile.OpenAsync(FileAccessMode.ReadWrite);
                richEditBox.Document.SaveToStream(textOptions, stream);
            }
            catch (Exception exc)
            {
                message = exc.Message;
            }

            if (message != null)
            {
                MessageDialog msgdlg = new MessageDialog("The file could not be saved. " +
                                                         "Windows reports the following error: " +
                                                         message, "RichTextEditor");
                await msgdlg.ShowAsync();
            }
        }
    }
}