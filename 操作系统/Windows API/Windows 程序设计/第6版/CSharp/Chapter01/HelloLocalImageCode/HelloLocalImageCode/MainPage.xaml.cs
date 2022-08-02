using System;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media.Imaging;

namespace HelloLocalImageCode
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
            image.Source = new BitmapImage(new Uri("ms-appx:///Images/Greeting.png"));
        }
    }
}
