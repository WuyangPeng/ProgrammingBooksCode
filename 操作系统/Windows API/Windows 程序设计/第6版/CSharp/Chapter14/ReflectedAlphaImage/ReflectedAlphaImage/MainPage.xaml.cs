using System;
using System.IO;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Storage.Streams;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media.Imaging;

namespace ReflectedAlphaImage
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
            Loaded += OnMainPageLoaded;
        }

        async void OnMainPageLoaded(object sender, RoutedEventArgs e)
        {
            Uri uri = new Uri("http://www.charlespetzold.com/pw6/PetzoldJersey.jpg");
            RandomAccessStreamReference streamRef = RandomAccessStreamReference.CreateFromUri(uri);

            // Create a buffer for reading the stream
            Windows.Storage.Streams.Buffer buffer = null;

            // Read the entire file
            using (IRandomAccessStreamWithContentType fileStream = await streamRef.OpenReadAsync())
            {
                buffer = new Windows.Storage.Streams.Buffer((uint)fileStream.Size);
                await fileStream.ReadAsync(buffer, (uint)fileStream.Size, InputStreamOptions.None);
            }

            // Create WriteableBitmap with unknown size
            WriteableBitmap bitmap = new WriteableBitmap(1, 1);

            // Create a memory stream for transferring the data
            using (InMemoryRandomAccessStream memoryStream = new InMemoryRandomAccessStream())
            {
                await memoryStream.WriteAsync(buffer);
                memoryStream.Seek(0);

                // Use the memory stream as the Bitmap source
                bitmap.SetSource(memoryStream);
            }

            // Now get the pixels from the bitmap
            byte[] pixels = new byte[4 * bitmap.PixelWidth * bitmap.PixelHeight];
            int index = 0;

            using (Stream pixelStream = bitmap.PixelBuffer.AsStream())
            {
                await pixelStream.ReadAsync(pixels, 0, pixels.Length);

                // Apply opacity to the pixels
                for (int y = 0; y < bitmap.PixelHeight; y++)
                {
                    double opacity = (double)y / bitmap.PixelHeight;

                    for (int x = 0; x < bitmap.PixelWidth; x++)
                        for (int i = 0; i < 4; i++)
                        {
                            pixels[index] = (byte)(opacity * pixels[index]);
                            index++;
                        }
                }

                // Put the pixels back in the bitmap
                pixelStream.Seek(0, SeekOrigin.Begin);
                await pixelStream.WriteAsync(pixels, 0, pixels.Length);
            }
            bitmap.Invalidate();
            reflectedImage.Source = bitmap;
        }
    }
}
