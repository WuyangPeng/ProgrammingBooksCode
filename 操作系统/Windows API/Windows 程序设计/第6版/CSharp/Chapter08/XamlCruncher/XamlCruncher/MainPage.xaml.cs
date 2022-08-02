using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using Windows.ApplicationModel;
using Windows.Globalization;
using Windows.Globalization.Fonts;
using Windows.Storage;
using Windows.Storage.Pickers;
using Windows.UI;
using Windows.UI.Popups;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Markup;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

namespace XamlCruncher
{
    public sealed partial class MainPage : Page
    {
        Brush textBlockBrush, textBoxBrush, errorBrush;
        AppSettings appSettings;
        StorageFile loadedStorageFile;

        public MainPage()
        {
            this.InitializeComponent();

            // Set brushes
            textBlockBrush = Resources["ApplicationForegroundThemeBrush"] as SolidColorBrush;
            textBoxBrush = Resources["TextBoxForegroundThemeBrush"] as SolidColorBrush;
            errorBrush = new SolidColorBrush(Colors.Red);

            // Why aren't these set in the generated C# files?
            editBox = splitContainer.Child1 as TabbableTextBox;
            resultContainer = splitContainer.Child2 as RulerContainer;

            // Set a fixed-pitch font for the TextBox
            Language language = new Language(Windows.Globalization.Language.CurrentInputMethodLanguageTag); 
            LanguageFontGroup languageFontGroup = new LanguageFontGroup(language.LanguageTag);
            LanguageFont languageFont = languageFontGroup.FixedWidthTextFont;
            editBox.FontFamily = new FontFamily(languageFont.FontFamily);

            Loaded += OnLoaded;
            Application.Current.Suspending += OnApplicationSuspending;
        }

        async void OnLoaded(object sender, RoutedEventArgs args)
        {
            // Load AppSettings and set to DataContext
            appSettings = new AppSettings();
            this.DataContext = appSettings;

            // Load any file that may have been saved
            StorageFolder localFolder = ApplicationData.Current.LocalFolder;
            StorageFile storageFile = await localFolder.CreateFileAsync("XamlCruncher.xaml",
                                                    CreationCollisionOption.OpenIfExists);
            editBox.Text = await FileIO.ReadTextAsync(storageFile);

            if (editBox.Text.Length == 0)
                await SetDefaultXamlFile();

            // Other initialization
            ParseText();
            editBox.Focus(FocusState.Programmatic);
            DisplayLineAndColumn();

            Application.Current.UnhandledException += (excSender, excArgs) =>
                {
                    SetErrorText(excArgs.Message);
                    excArgs.Handled = true;
                };
        }

        async void OnApplicationSuspending(object sender, SuspendingEventArgs args)
        {
            // Save application settings
            appSettings.Save();

            // Save text content
            SuspendingDeferral deferral = args.SuspendingOperation.GetDeferral();
            await PathIO.WriteTextAsync("ms-appdata:///local/XamlCruncher.xaml", editBox.Text);
            deferral.Complete();
        }

        async Task SetDefaultXamlFile()
        {
            editBox.Text =
                "<Page xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\"\r\n" +
                "      xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\">\r\n\r\n" +
                "    <TextBlock Text=\"Hello, Windows 8!\"\r\n" +
                "               FontSize=\"48\" />\r\n\r\n" +
                "</Page>";

            editBox.IsModified = false;
            loadedStorageFile = null;
            filenameText.Text = "";
        }

        void OnRefreshAppBarButtonClick(object sender, RoutedEventArgs args)
        {
            ParseText();
            this.BottomAppBar.IsOpen = false;
        }

        void OnSettingsAppBarButtonClick(object sender, RoutedEventArgs args)
        {
            SettingsDialog settingsDialog = new SettingsDialog();
            settingsDialog.DataContext = appSettings;

            Popup popup = new Popup
            {
                Child = settingsDialog,
                IsLightDismissEnabled = true
            };

            settingsDialog.Loaded += (dialogSender, dialogArgs) =>
                {
                    popup.VerticalOffset = this.ActualHeight - settingsDialog.ActualHeight 
                                                             - this.BottomAppBar.ActualHeight - 24;
                    popup.HorizontalOffset = 24;
                };

            popup.Closed += (popupSender, popupArgs) =>
                {
                    this.BottomAppBar.IsOpen = false;
                };
            popup.IsOpen = true;
        }

        async void OnAddAppBarButtonClick(object sender, RoutedEventArgs args)
        {
            Button button = sender as Button;
            button.IsEnabled = false;
            await CheckIfOkToTrashFile(SetDefaultXamlFile);
            button.IsEnabled = true;
            this.BottomAppBar.IsOpen = false;
        }

        async void OnOpenAppBarButtonClick(object sender, RoutedEventArgs args)
        {
            Button button = sender as Button;
            button.IsEnabled = false;
            await CheckIfOkToTrashFile(LoadFileFromOpenPicker);
            button.IsEnabled = true;
            this.BottomAppBar.IsOpen = false;
        }

        async Task CheckIfOkToTrashFile(Func<Task> commandAction)
        {
            if (!editBox.IsModified)
            {
                await commandAction();
                return;
            }

            string message =
                String.Format("Do you want to save changes to {0}?",
                    loadedStorageFile == null ? "(untitled)" : loadedStorageFile.Name);

            MessageDialog msgdlg = new MessageDialog(message, "XAML Cruncher");
            msgdlg.Commands.Add(new UICommand("Save", null, "save"));
            msgdlg.Commands.Add(new UICommand("Don't Save", null, "dont"));
            msgdlg.Commands.Add(new UICommand("Cancel", null, "cancel"));
            msgdlg.DefaultCommandIndex = 0;
            msgdlg.CancelCommandIndex = 2;
            IUICommand command = await msgdlg.ShowAsync();

            if ((string)command.Id == "cancel")
                return;

            if ((string)command.Id == "dont")
            {
                await commandAction();
                return;
            }

            if (loadedStorageFile == null)
            {
                StorageFile storageFile = await GetFileFromSavePicker();

                if (storageFile == null)
                    return;

                loadedStorageFile = storageFile;
            }

            await SaveXamlToFile(loadedStorageFile);
            await commandAction();
        }

        async Task LoadFileFromOpenPicker()
        {
            FileOpenPicker picker = new FileOpenPicker();
            picker.FileTypeFilter.Add(".xaml");
            StorageFile storageFile = await picker.PickSingleFileAsync();

            if (storageFile != null)
            {
                string exception = null;

                try
                {
                    editBox.Text = await FileIO.ReadTextAsync(storageFile);
                }
                catch (Exception exc)
                {
                    exception = exc.Message;
                }

                if (exception != null)
                {
                    string message = String.Format("Could not load file {0}: {1}",
                                                   storageFile.Name, exception);
                    MessageDialog msgdlg = new MessageDialog(message, "XAML Cruncher");
                    await msgdlg.ShowAsync();
                }
                else
                {
                    editBox.IsModified = false;
                    loadedStorageFile = storageFile;
                    filenameText.Text = loadedStorageFile.Path;
                }
            }
        }

        async void OnSaveAsAppBarButtonClick(object sender, RoutedEventArgs args)
        {
            StorageFile storageFile = await GetFileFromSavePicker();

            if (storageFile == null)
                return;

            await SaveXamlToFile(storageFile);
        }

        async void OnSaveAppBarButtonClick(object sender, RoutedEventArgs args)
        {
            Button button = sender as Button;
            button.IsEnabled = false;

            if (loadedStorageFile != null)
            {
                await SaveXamlToFile(loadedStorageFile);
            }
            else
            {
                StorageFile storageFile = await GetFileFromSavePicker();

                if (storageFile != null)
                {
                    await SaveXamlToFile(storageFile);
                }
            }
            button.IsEnabled = true;
        }

        async Task<StorageFile> GetFileFromSavePicker()
        {
            FileSavePicker picker = new FileSavePicker();
            picker.DefaultFileExtension = ".xaml";
            picker.FileTypeChoices.Add("XAML", new List<string> { ".xaml" });
            picker.SuggestedSaveFile = loadedStorageFile;
            return await picker.PickSaveFileAsync();
        }

        async Task SaveXamlToFile(StorageFile storageFile)
        {
            loadedStorageFile = storageFile;
            string exception = null;

            try
            {
                await FileIO.WriteTextAsync(storageFile, editBox.Text);
            }
            catch (Exception exc)
            {
                exception = exc.Message;
            }

            if (exception != null)
            {
                string message = String.Format("Could not save file {0}: {1}",
                                               storageFile.Name, exception);
                MessageDialog msgdlg = new MessageDialog(message, "XAML Cruncher");
                await msgdlg.ShowAsync();
            }
            else
            {
                editBox.IsModified = false;
                filenameText.Text = storageFile.Path;
            }
        }

        // TextBox events
        void OnEditBoxSelectionChanged(object sender, RoutedEventArgs args)
        {
            DisplayLineAndColumn();
        }

        void DisplayLineAndColumn()
        {
            int line, col;
            editBox.GetPositionFromIndex(editBox.SelectionStart, out line, out col);
            lineColText.Text = String.Format("Line {0} Col {1}", line + 1, col + 1);

            if (editBox.SelectionLength > 0)
            {
                editBox.GetPositionFromIndex(editBox.SelectionStart + editBox.SelectionLength - 1, 
                                             out line, out col);
                lineColText.Text += String.Format(" - Line {0} Col {1}", line + 1, col + 1);
            }
        }

        void OnEditBoxTextChanged(object sender, RoutedEventArgs e)
        {
            if (appSettings.AutoParsing)
                ParseText();
        }

        void ParseText()
        {
            object result = null;

            try
            {
                result = XamlReader.Load(editBox.Text);
            }
            catch (Exception exc)
            {
                SetErrorText(exc.Message);
                return;
            }

            if (result == null)
            {
                SetErrorText("Null result");
            }
            else if (!(result is UIElement))
            {
                SetErrorText("Result is " + result.GetType().Name);
            }
            else
            {
                resultContainer.Child = result as UIElement;
                SetOkText();
                return;
            }
        }
            
        void SetErrorText(string text)
        {
            SetStatusText(text, errorBrush, errorBrush);
        }

        void SetOkText()
        {
            SetStatusText("OK", textBlockBrush, textBoxBrush);
        }

        void SetStatusText(string text, Brush statusBrush, Brush editBrush)
        {
            statusText.Text = text;
            statusText.Foreground = statusBrush;
            editBox.Foreground = editBrush;
        }
    }
}
