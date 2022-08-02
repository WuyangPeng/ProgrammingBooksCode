using System;
using System.Collections.Generic;
using Windows.Storage;
using Windows.Storage.Pickers;
using Windows.Storage.Streams;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace PrimitivePad
{
    public sealed partial class MainPage : Page
    {
        ApplicationDataContainer appData = ApplicationData.Current.LocalSettings;

        public MainPage()
        {
            this.InitializeComponent();

            Loaded += (sender, args) =>
                {
                    if (appData.Values.ContainsKey("TextWrapping"))
                        txtbox.TextWrapping = (TextWrapping)appData.Values["TextWrapping"];

                    wrapButton.IsChecked = txtbox.TextWrapping == TextWrapping.Wrap;
                    wrapButton.Content = (bool)wrapButton.IsChecked ? "Wrap" : "No Wrap";

                    txtbox.Focus(FocusState.Programmatic);
                };
        }

        async void OnFileOpenButtonClick(object sender, RoutedEventArgs args)
        {
            FileOpenPicker picker = new FileOpenPicker();
            picker.FileTypeFilter.Add(".txt");
            StorageFile storageFile = await picker.PickSingleFileAsync();

            // If user presses Cancel, result is null
            if (storageFile == null)
                return;

            using (IRandomAccessStream stream = await storageFile.OpenReadAsync())
            {
                using (DataReader dataReader = new DataReader(stream))
                {
                    uint length = (uint)stream.Size;
                    await dataReader.LoadAsync(length);
                    txtbox.Text = dataReader.ReadString(length);
                }
            }
        }

        async void OnFileSaveAsButtonClick(object sender, RoutedEventArgs args)
        {
            FileSavePicker picker = new FileSavePicker();
            picker.DefaultFileExtension = ".txt";
            picker.FileTypeChoices.Add("Text", new List<string> { ".txt" });
            StorageFile storageFile = await picker.PickSaveFileAsync();

            // If user presses Cancel, result is null
            if (storageFile == null)
                return;

            using (IRandomAccessStream stream = await storageFile.OpenAsync(FileAccessMode.ReadWrite))
            {
                using (DataWriter dataWriter = new DataWriter(stream))
                {
                    dataWriter.WriteString(txtbox.Text);
                    await dataWriter.StoreAsync();
                }
            }
        }

        void OnWrapButtonChecked(object sender, RoutedEventArgs args)
        {
            txtbox.TextWrapping = (bool)wrapButton.IsChecked ? TextWrapping.Wrap : 
                                                               TextWrapping.NoWrap;
            wrapButton.Content = (bool)wrapButton.IsChecked ? "Wrap" : "No Wrap";
            appData.Values["TextWrapping"] = (int)txtbox.TextWrapping;
        }
    }
}
