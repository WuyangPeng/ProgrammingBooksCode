using System;
using System.Collections.Generic;
using Windows.ApplicationModel;
using Windows.Foundation;
using Windows.Storage;
using Windows.Storage.Pickers;
using Windows.Storage.Streams;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;

namespace AppBarPad
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();

            // Get local settings object
            ApplicationDataContainer appData = ApplicationData.Current.LocalSettings;

            Loaded += async (sender, args) =>
                {
                    // Load TextBox settings
                    if (appData.Values.ContainsKey("TextWrapping"))
                        txtbox.TextWrapping = (TextWrapping)appData.Values["TextWrapping"];

                    if (appData.Values.ContainsKey("FontSize"))
                        txtbox.FontSize = (double)appData.Values["FontSize"];

                    // Load TextBox content
                    StorageFolder localFolder = ApplicationData.Current.LocalFolder;
                    StorageFile storageFile = await localFolder.CreateFileAsync("AppBarPad.txt",
                                                        CreationCollisionOption.OpenIfExists);
                    txtbox.Text = await FileIO.ReadTextAsync(storageFile);

                    // Enable the TextBox and give it input focus
                    txtbox.IsEnabled = true;
                    txtbox.Focus(FocusState.Programmatic);
                };

            Application.Current.Suspending += async (sender, args) =>
            {
                // Save TextBox settings
                appData.Values["TextWrapping"] = (int)txtbox.TextWrapping;
                appData.Values["FontSize"] = txtbox.FontSize;

                // Save TextBox content
                SuspendingDeferral deferral = args.SuspendingOperation.GetDeferral();
                await PathIO.WriteTextAsync("ms-appdata:///local/AppBarPad.txt", txtbox.Text);
                deferral.Complete();
            };
        }

        void OnFontIncreaseAppBarButtonClick(object sender, RoutedEventArgs args)
        {
            ChangeFontSize(1.1);
        }

        void OnFontDecreaseAppBarButtonClick(object sender, RoutedEventArgs args)
        {
            ChangeFontSize(1/1.1);
        }

        void ChangeFontSize(double multiplier)
        {
            txtbox.FontSize *= multiplier;
        }

        void OnWrapOptionAppBarButtonClick(object sender, RoutedEventArgs args)
        {
            // Create dialog
            WrapOptionsDialog wrapOptionsDialog = new WrapOptionsDialog
            {
                TextWrapping = txtbox.TextWrapping
            };

            // Bind dialog to TextBox
            Binding binding = new Binding
            {
                Source = wrapOptionsDialog,
                Path = new PropertyPath("TextWrapping"),
                Mode = BindingMode.TwoWay
            };
            txtbox.SetBinding(TextBox.TextWrappingProperty, binding);

            // Create popup
            Popup popup = new Popup
            {
                Child = wrapOptionsDialog,
                IsLightDismissEnabled = true
            };

            // Adjust location based on content size
            wrapOptionsDialog.Loaded += (dialogSender, dialogArgs) =>
            {
                // Get Button location relative to screen
                Button btn = sender as Button;
                Point pt = btn.TransformToVisual(null).TransformPoint(new Point(btn.ActualWidth / 2, 
                                                                                btn.ActualHeight / 2));

                popup.HorizontalOffset = pt.X - wrapOptionsDialog.ActualWidth / 2;

                popup.VerticalOffset = this.ActualHeight - wrapOptionsDialog.ActualHeight
                                                         - this.BottomAppBar.ActualHeight - 48;
            };

            // Open the popup
            popup.IsOpen = true;
        }

        async void OnOpenAppBarButtonClick(object sender, RoutedEventArgs args)
        {
            FileOpenPicker picker = new FileOpenPicker();
            picker.FileTypeFilter.Add(".txt");
            StorageFile storageFile = await picker.PickSingleFileAsync();

            // If user presses Cancel, result is null
            if (storageFile == null)
                return;

            txtbox.Text = await FileIO.ReadTextAsync(storageFile);
        }

        async void OnSaveAsAppBarButtonClick(object sender, RoutedEventArgs args)
        {
            FileSavePicker picker = new FileSavePicker();
            picker.DefaultFileExtension = ".txt";
            picker.FileTypeChoices.Add("Text", new List<string> { ".txt" });
            StorageFile storageFile = await picker.PickSaveFileAsync();

            // If user presses Cancel, result is null
            if (storageFile == null)
                return;

            await FileIO.WriteTextAsync(storageFile, txtbox.Text);
        }
    }
}
