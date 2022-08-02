using System.IO;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media.Imaging;

namespace CustomGradient
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

            for (int y = 0; y < bitmap.PixelHeight; y++)
                for (int x = 0; x < bitmap.PixelWidth; x++)
                {
                    int index = 4 * (y * bitmap.PixelWidth + x);
                    pixels[index + 0] = (byte)x;    // Blue
                    pixels[index + 1] = 0;          // Green
                    pixels[index + 2] = (byte)y;    // Red
                    pixels[index + 3] = 255;        // Alpha
                }

            using (Stream pixelStream = bitmap.PixelBuffer.AsStream())
            {
                await pixelStream.WriteAsync(pixels, 0, pixels.Length);
            }
            bitmap.Invalidate();
            image.Source = bitmap;
        }
    }
}
