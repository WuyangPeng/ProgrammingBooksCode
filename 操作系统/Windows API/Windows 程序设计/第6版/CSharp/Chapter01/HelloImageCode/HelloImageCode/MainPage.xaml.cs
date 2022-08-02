using System;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media.Imaging;

namespace HelloImageCode
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();

            Uri uri = new Uri("http://www.charlespetzold.com/pw6/PetzoldJersey.jpg");
            BitmapImage bitmap = new BitmapImage(uri);
            Image image = new Image();
            image.Source = bitmap;
            contentGrid.Children.Add(image);
        }
    }
}
