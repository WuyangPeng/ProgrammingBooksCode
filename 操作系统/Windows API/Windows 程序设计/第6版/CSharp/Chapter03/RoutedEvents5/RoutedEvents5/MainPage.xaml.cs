using System;
using Windows.UI;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;

namespace RoutedEvents5
{
    public sealed partial class MainPage : Page
    {
        Random rand = new Random();
        byte[] rgb = new byte[3];

        public MainPage()
        {
            this.InitializeComponent();
        }

        void OnTextBlockTapped(object sender, TappedRoutedEventArgs args)
        {
            TextBlock txtblk = sender as TextBlock;
            txtblk.Foreground = GetRandomBrush();
            args.Handled = true;
        }

        protected override void OnTapped(TappedRoutedEventArgs args)
        {
            contentGrid.Background = GetRandomBrush();
            base.OnTapped(args);
        }

        Brush GetRandomBrush()
        {
            rand.NextBytes(rgb);
            Color clr = Color.FromArgb(255, rgb[0], rgb[1], rgb[2]);
            return new SolidColorBrush(clr);
        }
    }
}
