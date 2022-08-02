using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Threading.Tasks;
using Windows.Graphics.Imaging;
using Windows.Storage;
using Windows.Storage.Pickers;
using Windows.Storage.Streams;
using Windows.UI.Popups;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media.Imaging;

namespace FingerPaint
{
    public sealed partial class MainPage : Page
    {
        WriteableBitmap bitmap;
        Stream pixelStream;
        byte[] pixels;

        async Task CreateNewBitmapAndPixelArray()
        {
            bitmap = new WriteableBitmap((int)this.ActualWidth, (int)this.ActualHeight);
            pixels = new byte[4 * bitmap.PixelWidth * bitmap.PixelHeight];

            // Set whole bitmap to white
            for (int index = 0; index < pixels.Length; index++)
                pixels[index] = 0xFF;

            await InitializeBitmap();

            appSettings.LoadedFilePath = null;
            appSettings.LoadedFilename = null;
            appSettings.IsImageModified = false;
        }

        async Task LoadBitmapFromFile(StorageFile storageFile)
        {
            using (IRandomAccessStreamWithContentType stream = await storageFile.OpenReadAsync())
            {
                BitmapDecoder decoder = await BitmapDecoder.CreateAsync(stream);
                BitmapFrame bitmapframe = await decoder.GetFrameAsync(0);
                PixelDataProvider dataProvider =
                    await bitmapframe.GetPixelDataAsync(BitmapPixelFormat.Bgra8,
                                                        BitmapAlphaMode.Premultiplied,
                                                        new BitmapTransform(),
                                                        ExifOrientationMode.RespectExifOrientation,
                                                        ColorManagementMode.ColorManageToSRgb);
                pixels = dataProvider.DetachPixelData();
                bitmap = new WriteableBitmap((int)bitmapframe.PixelWidth,
                                             (int)bitmapframe.PixelHeight);
                await InitializeBitmap();
            }
        }

        async Task InitializeBitmap()
        {
            pixelStream = bitmap.PixelBuffer.AsStream();
            await pixelStream.WriteAsync(pixels, 0, pixels.Length);
            bitmap.Invalidate();
            image.Source = bitmap;
            CalculateImageScaleAndOffset();
        }

        async void OnAddAppBarButtonClick(object sender, RoutedEventArgs args)
        {
            Button button = sender as Button;
            button.IsEnabled = false;

            await CheckIfOkToTrashFile(CreateNewBitmapAndPixelArray);

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
            if (!appSettings.IsImageModified)
            {
                await commandAction();
                return;
            }

            string message =
                String.Format("Do you want to save changes to {0}?",
                              appSettings.LoadedFilePath ?? "(untitled)");

            MessageDialog msgdlg = new MessageDialog(message, "Finger Paint");
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

            if (appSettings.LoadedFilePath == null)
            {
                StorageFile storageFile = await GetFileFromSavePicker();

                if (storageFile == null)
                    return;

                appSettings.LoadedFilePath = storageFile.Path;
                appSettings.LoadedFilename = storageFile.Name;
            }

            string exception = null;

            try
            {
                await SaveBitmapToFile(appSettings.LoadedFilePath);
            }
            catch (Exception exc)
            {
                exception = exc.Message;
            }

            if (exception != null)
            {
                msgdlg = new MessageDialog("The image file could not be saved. " +
                                           "The system reports an error of: " + exception,
                                           "Finger Paint");
                await msgdlg.ShowAsync();
                return;
            }

            await commandAction();
        }

        async Task LoadFileFromOpenPicker()
        {
            // Create FileOpenPicker
            FileOpenPicker picker = new FileOpenPicker();
            picker.SuggestedStartLocation = PickerLocationId.PicturesLibrary;

            // Initialize with filename extensions
            IReadOnlyList<BitmapCodecInformation> codecInfos =
                                    BitmapDecoder.GetDecoderInformationEnumerator();

            foreach (BitmapCodecInformation codecInfo in codecInfos)
                foreach (string extension in codecInfo.FileExtensions)
                    picker.FileTypeFilter.Add(extension);

            // Get the selected file
            StorageFile storageFile = await picker.PickSingleFileAsync();

            if (storageFile == null)
                return;

            string exception = null;

            try
            {
                await LoadBitmapFromFile(storageFile);
            }
            catch (Exception exc)
            {
                exception = exc.Message;
            }

            if (exception != null)
            {
                MessageDialog msgdlg =
                    new MessageDialog("The image file could not be loaded. " +
                                      "The system reports an error of: " + exception,
                                      "Finger Paint");
                await msgdlg.ShowAsync();
                return;
            }

            appSettings.LoadedFilePath = storageFile.Path;
            appSettings.LoadedFilename = storageFile.Name;
            appSettings.IsImageModified = false;
        }

        async void OnSaveAppBarButtonClick(object sender, RoutedEventArgs args)
        {
            Button button = sender as Button;
            button.IsEnabled = false;

            if (appSettings.LoadedFilePath != null)
            {
                await SaveWithErrorNotification(appSettings.LoadedFilePath);
            }
            else
            {
                StorageFile storageFile = await GetFileFromSavePicker();

                if (storageFile == null)
                    return;

                await SaveWithErrorNotification(storageFile);
            }

            button.IsEnabled = true;
        }

        async void OnSaveAsAppBarButtonClick(object sender, RoutedEventArgs args)
        {
            StorageFile storageFile = await GetFileFromSavePicker();

            if (storageFile == null)
                return;

            await SaveWithErrorNotification(storageFile);
        }

        async Task<StorageFile> GetFileFromSavePicker()
        {
            FileSavePicker picker = new FileSavePicker();
            picker.SuggestedStartLocation = PickerLocationId.PicturesLibrary;
            picker.SuggestedFileName = appSettings.LoadedFilename ?? "MyFingerPainting";

            // Get the encoder information
            Dictionary<string, Guid> imageTypes = new Dictionary<string, Guid>();
            IReadOnlyList<BitmapCodecInformation> codecInfos =
                                    BitmapEncoder.GetEncoderInformationEnumerator();

            foreach (BitmapCodecInformation codecInfo in codecInfos)
            {
                List<string> extensions = new List<string>();

                foreach (string extension in codecInfo.FileExtensions)
                    extensions.Add(extension);

                string filetype = codecInfo.FriendlyName.Split(' ')[0];
                picker.FileTypeChoices.Add(filetype, extensions);

                foreach (string mimeType in codecInfo.MimeTypes)
                    imageTypes.Add(mimeType, codecInfo.CodecId);
            }

            // Get a selected StorageFile
            return await picker.PickSaveFileAsync();
        }

        async Task<bool> SaveWithErrorNotification(string filename)
        {
            StorageFile storageFile = await StorageFile.GetFileFromPathAsync(filename);
            return await SaveWithErrorNotification(storageFile);
        }

        async Task<bool> SaveWithErrorNotification(StorageFile storageFile)
        {
            string exception = null;

            try
            {
                await SaveBitmapToFile(storageFile);
            }
            catch (Exception exc)
            {
                exception = exc.Message;
            }

            if (exception != null)
            {
                MessageDialog msgdlg =
                    new MessageDialog("The image file could not be saved. " +
                                      "The system reports an error of: " + exception,
                                      "Finger Paint");
                await msgdlg.ShowAsync();
                return false;
            }

            appSettings.LoadedFilePath = storageFile.Path;
            appSettings.IsImageModified = false;
            return true;
        }

        async Task SaveBitmapToFile(string filename)
        {
            StorageFile storageFile = await StorageFile.GetFileFromPathAsync(filename);
            await SaveBitmapToFile(storageFile);
        }

        async Task SaveBitmapToFile(StorageFile storageFile)
        {
            using (IRandomAccessStream fileStream = await storageFile.OpenAsync(FileAccessMode.ReadWrite))
            {
                BitmapEncoder encoder = await BitmapEncoder.CreateAsync(BitmapEncoder.PngEncoderId, fileStream);
                encoder.SetPixelData(BitmapPixelFormat.Bgra8, BitmapAlphaMode.Premultiplied,
                                     (uint)bitmap.PixelWidth, (uint)bitmap.PixelHeight,
                                     96, 96, pixels);
                await encoder.FlushAsync();
            }
        }
    }
}
