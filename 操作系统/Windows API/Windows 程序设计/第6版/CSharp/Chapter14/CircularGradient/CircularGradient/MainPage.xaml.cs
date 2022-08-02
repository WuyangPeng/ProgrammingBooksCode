using System;
using System.Runtime.InteropServices.WindowsRuntime;
using System.IO;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media.Imaging;

namespace CircularGradient
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
            Loaded += OnMainPageLoaded;
        }

        async void OnMainPageLoaded(object sender, RoutedEventArgs args)
        {
            WriteableBitmap bitmap = new WriteableBitmap(256, 256);
            byte[] pixels = new byte[4 * bitmap.PixelWidth * bitmap.PixelHeight];
            int index = 0;
            int centerX = bitmap.PixelWidth / 2;
            int centerY = bitmap.PixelHeight / 2;

            for (int y = 0; y < bitmap.PixelHeight; y++)
                for (int x = 0; x < bitmap.PixelWidth; x++)
                {
                    double angle = 
                        Math.Atan2(((double)y - centerY) / bitmap.PixelHeight,
                                   ((double)x - centerX) / bitmap.PixelWidth);
                    double fraction = angle / (2 * Math.PI);
                    pixels[index++] = (byte)(fraction * 255);       // Blue
                    pixels[index++] = 0;                            // Green
                    pixels[index++] = (byte)(255 * (1 - fraction)); // Red
                    pixels[index++] = 255;                          // Alpha
                }

            using (Stream pixelStream = bitmap.PixelBuffer.AsStream())
            {
                await pixelStream.WriteAsync(pixels, 0, pixels.Length);
            }
            bitmap.Invalidate();
            imageBrush.ImageSource = bitmap;
        }
    }
}
