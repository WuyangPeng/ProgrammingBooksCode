using System;
using Windows.UI;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;

namespace RoutedEvents6
{
    public sealed partial class MainPage : Page
    {
        Random rand = new Random();
        byte[] rgb = new byte[3];

        public MainPage()
        {
            this.InitializeComponent();

            this.AddHandler(UIElement.TappedEvent,
                            new TappedEventHandler(OnPageTapped),
                            true);
        }

        void OnTextBlockTapped(object sender, TappedRoutedEventArgs args)
        {
            TextBlock txtblk = sender as TextBlock;
            txtblk.Foreground = GetRandomBrush();
            args.Handled = true;
        }

        void OnPageTapped(object sender, TappedRoutedEventArgs args)
        {
            contentGrid.Background = GetRandomBrush();
        }

        Brush GetRandomBrush()
        {
            rand.NextBytes(rgb);
            Color clr = Color.FromArgb(255, rgb[0], rgb[1], rgb[2]);
            return new SolidColorBrush(clr);
        }
    }
}
