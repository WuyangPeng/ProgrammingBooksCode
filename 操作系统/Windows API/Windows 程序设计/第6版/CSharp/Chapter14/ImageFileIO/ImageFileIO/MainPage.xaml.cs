using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Graphics.Imaging;
using Windows.Storage;
using Windows.Storage.Pickers;
using Windows.Storage.Streams;
using Windows.UI.Popups;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media.Imaging;

namespace ImageFileIO
{
    public sealed partial class MainPage : Page
    {
        double dpiX, dpiY;

        public MainPage()
        {
            this.InitializeComponent();
        }

        async void OnOpenAppBarButtonClick(object sender, RoutedEventArgs args)
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

            // Open the stream and create a decoder
            BitmapDecoder decoder = null;

            using (IRandomAccessStreamWithContentType stream = await storageFile.OpenReadAsync())
            {
                string exception = null;

                try
                {
                    decoder = await BitmapDecoder.CreateAsync(stream);
                }
                catch (Exception exc)
                {
                    exception = exc.Message;
                }

                if (exception != null)
                {
                    MessageDialog msgdlg = 
                        new MessageDialog("That particular image file could not be loaded. " +
                                          "The system reports on error of: " + exception);
                    await msgdlg.ShowAsync();
                    return;
                }

                // Get the first frame
                BitmapFrame bitmapFrame = await decoder.GetFrameAsync(0);

                // Set information title
                txtblk.Text = String.Format("{0}: {1} x {2} {3} {4} x {5} DPI", 
                                            storageFile.Name, 
                                            bitmapFrame.PixelWidth, bitmapFrame.PixelHeight, 
                                            bitmapFrame.BitmapPixelFormat, 
                                            bitmapFrame.DpiX, bitmapFrame.DpiY);
                // Save the resolution
                dpiX = bitmapFrame.DpiX;
                dpiY = bitmapFrame.DpiY;

                // Get the pixels
                PixelDataProvider dataProvider = 
                    await bitmapFrame.GetPixelDataAsync(BitmapPixelFormat.Bgra8, 
                                                        BitmapAlphaMode.Premultiplied, 
                                                        new BitmapTransform(), 
                                                        ExifOrientationMode.RespectExifOrientation, 
                                                        ColorManagementMode.ColorManageToSRgb);

                byte[] pixels = dataProvider.DetachPixelData();

                // Create WriteableBitmap and set the pixels
                WriteableBitmap bitmap = new WriteableBitmap((int)bitmapFrame.PixelWidth, 
                                                             (int)bitmapFrame.PixelHeight);

                using (Stream pixelStream = bitmap.PixelBuffer.AsStream())
                {
                    await pixelStream.WriteAsync(pixels, 0, pixels.Length);
                }

                // Invalidate the WriteableBitmap and set as Image source
                bitmap.Invalidate();
                image.Source = bitmap;
            }

            // Enable the other buttons
            saveAsButton.IsEnabled = true;
            rotateLeftButton.IsEnabled = true;
            rotateRightButton.IsEnabled = true;
        }

        async void OnSaveAsAppBarButtonClick(object sender, RoutedEventArgs args)
        {
            FileSavePicker picker = new FileSavePicker();
            picker.SuggestedStartLocation = PickerLocationId.PicturesLibrary;

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
            StorageFile storageFile = await picker.PickSaveFileAsync();

            if (storageFile == null)
                return;

            // Open the StorageFile
            using (IRandomAccessStream fileStream = 
                                    await storageFile.OpenAsync(FileAccessMode.ReadWrite))
            {
                // Create an encoder
                Guid codecId = imageTypes[storageFile.ContentType];
                BitmapEncoder encoder = await BitmapEncoder.CreateAsync(codecId, fileStream);

                // Get the pixels from the existing WriteableBitmap
                WriteableBitmap bitmap = image.Source as WriteableBitmap;
                byte[] pixels = new byte[4 * bitmap.PixelWidth * bitmap.PixelHeight];

                using (Stream pixelStream = bitmap.PixelBuffer.AsStream())
                {
                    await pixelStream.ReadAsync(pixels, 0, pixels.Length);
                }

                // Write those pixels to the first frame
                encoder.SetPixelData(BitmapPixelFormat.Bgra8, BitmapAlphaMode.Premultiplied,
                                     (uint)bitmap.PixelWidth, (uint)bitmap.PixelHeight,
                                     dpiX, dpiY, pixels);

                await encoder.FlushAsync();
            }
        }

        void OnRotateLeftAppBarButtonClick(object sender, RoutedEventArgs args)
        {
            Rotate((BitmapSource bitmap, int x, int y) =>
                {
                    return 4 * (bitmap.PixelWidth * x + (bitmap.PixelWidth - y - 1));
                });
        }

        void OnRotateRightAppBarButtonClick(object sender, RoutedEventArgs args)
        {
            Rotate((BitmapSource bitmap, int x, int y) =>
                {
                    return 4 * (bitmap.PixelWidth * (bitmap.PixelHeight - x - 1) + y);
                });
        }

        async void Rotate(Func<BitmapSource, int, int, int> calculateSourceIndex)
        {
            // Get the source bitmap pixels
            WriteableBitmap srcBitmap = image.Source as WriteableBitmap;
            byte[] srcPixels = new byte[4 * srcBitmap.PixelWidth * srcBitmap.PixelHeight];

            using (Stream pixelStream = srcBitmap.PixelBuffer.AsStream())
            {
                await pixelStream.ReadAsync(srcPixels, 0, srcPixels.Length);
            }

            // Create a destination bitmap and pixels array
            WriteableBitmap dstBitmap = 
                    new WriteableBitmap(srcBitmap.PixelHeight, srcBitmap.PixelWidth);
            byte[] dstPixels = new byte[4 * dstBitmap.PixelWidth * dstBitmap.PixelHeight];

            // Transfer the pixels
            int dstIndex = 0;
            for (int y = 0; y < dstBitmap.PixelHeight; y++)
                for (int x = 0; x < dstBitmap.PixelWidth; x++)
                {
                    int srcIndex = calculateSourceIndex(srcBitmap, x, y);

                    for (int i = 0; i < 4; i++)
                        dstPixels[dstIndex++] = srcPixels[srcIndex++];
                }

            // Move the pixels into the destination bitmap
            using (Stream pixelStream = dstBitmap.PixelBuffer.AsStream())
            {
                await pixelStream.WriteAsync(dstPixels, 0, dstPixels.Length);
            }
            dstBitmap.Invalidate();

            // Swap the DPIs
            double dpi = dpiX;
            dpiX = dpiY;
            dpiY = dpi;

            // Display the new bitmap
            image.Source = dstBitmap;
        }
    }
}
