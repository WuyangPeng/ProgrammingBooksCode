using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI;
using Windows.UI.Text;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

namespace DepthText
{
    public sealed partial class MainPage : Page
    {
        const int COUNT = 48;   // ~1/2 inch

        public MainPage()
        {
            this.InitializeComponent();

            Grid grid = this.Content as Grid;
            Brush foreground = this.Resources["ApplicationForegroundThemeBrush"] as Brush;
            Brush grayBrush = new SolidColorBrush(Colors.Gray);

            for (int i = 0; i < COUNT; i++)
            {
                bool firstOrLast = i == 0 || i == COUNT - 1;

                TextBlock txtblk = new TextBlock
                {
                    Text = "DEPTH",
                    FontSize = 192,
                    FontWeight = FontWeights.Bold,
                    HorizontalAlignment = HorizontalAlignment.Center,
                    VerticalAlignment = VerticalAlignment.Center,
                    RenderTransform = new TranslateTransform
                    {
                        X = COUNT - i - 1,
                        Y = i - COUNT + 1,
                    },
                    Foreground = firstOrLast ? foreground : grayBrush
                };
                grid.Children.Add(txtblk);
            }
        }
    }
}
