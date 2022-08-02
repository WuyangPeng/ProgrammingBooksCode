using System;
using Windows.ApplicationModel;
using Windows.Storage;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace QuickNotes
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
            StorageFolder localFolder = ApplicationData.Current.LocalFolder;
            StorageFile storageFile = await localFolder.CreateFileAsync("QuickNotes.txt", 
                                                            CreationCollisionOption.OpenIfExists);
            txtbox.Text = await FileIO.ReadTextAsync(storageFile);
            txtbox.SelectionStart = txtbox.Text.Length;
            txtbox.Focus(FocusState.Programmatic);
        }

        async void OnAppSuspending(object sender, SuspendingEventArgs args)
        {
            SuspendingDeferral deferral = args.SuspendingOperation.GetDeferral();
            await PathIO.WriteTextAsync("ms-appdata:///local/QuickNotes.txt", txtbox.Text);
            deferral.Complete();
        }
    }
}
