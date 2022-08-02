using System;
using Windows.Foundation;
using Windows.UI.Xaml.Controls;

namespace ImageBrushedSpiral
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();

            for (int angle = 0; angle < 3600; angle++)
            {
                double radians = Math.PI * angle / 180;
                double radius = angle / 3.6;
                double x = 1000 + radius * Math.Sin(radians);
                double y = 1000 - radius * Math.Cos(radians);
                polyline.Points.Add(new Point(x, y));
            }
        }
    }
}
