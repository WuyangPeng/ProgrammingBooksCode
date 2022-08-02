using System;
using Windows.Foundation;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Shapes;

namespace TapAndShowPoint
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
        }

        protected override void OnTapped(TappedRoutedEventArgs args)
        {
            Point pt = args.GetPosition(this);

            // Create dot
            Ellipse ellipse = new Ellipse
            {
                Width = 3,
                Height = 3,
                Fill = this.Foreground
            };

            Canvas.SetLeft(ellipse, pt.X);
            Canvas.SetTop(ellipse, pt.Y);
            canvas.Children.Add(ellipse);

            // Create text
            TextBlock txtblk = new TextBlock
            {
                Text = String.Format("({0})", pt),
                FontSize = 24,
            };

            Canvas.SetLeft(txtblk, pt.X);
            Canvas.SetTop(txtblk, pt.Y);
            canvas.Children.Add(txtblk);

            args.Handled = true;
            base.OnTapped(args);
        }
    }
}
