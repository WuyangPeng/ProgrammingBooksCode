using System;
using Windows.Storage;
using Windows.Storage.Streams;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace PrivateFonts
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
            Loaded += OnLoaded;
        }

        async void OnLoaded(object sender, RoutedEventArgs args)
        {
            StorageFolder localFolder = ApplicationData.Current.LocalFolder;
            bool folderExists = false;

            try
            {
                StorageFolder fontsFolder = await localFolder.GetFolderAsync("Fonts");
                folderExists = true;
            }
            catch (Exception)
            {
            }

            if (!folderExists)
            {
                StorageFolder fontsFolder = await localFolder.CreateFolderAsync("Fonts");

                string[] fonts = { "Kooten.ttf", "Linds.ttf", "Miramo.ttf", "Miramob.ttf", 
                                   "Peric.ttf", "pericl.ttf", "Pesca.ttf", "Pescab.ttf" };

                foreach (string font in fonts)
                {
                    // Copy from application content to IBuffer
                    string uri = "ms-appx:///Fonts/" + font;
                    IBuffer buffer = await PathIO.ReadBufferAsync(uri);

                    // Copy from IBuffer to local storage
                    StorageFile fontFile = await fontsFolder.CreateFileAsync(font);
                    await FileIO.WriteBufferAsync(fontFile, buffer);
                }
            }
        }
    }
}
