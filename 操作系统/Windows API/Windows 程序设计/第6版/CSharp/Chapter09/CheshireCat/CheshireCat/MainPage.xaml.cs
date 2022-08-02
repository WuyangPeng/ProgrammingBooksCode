﻿using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media.Animation;

namespace CheshireCat
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();

            Loaded += (sender, args) =>
                {
                    (this.Resources["storyboard"] as Storyboard).Begin();
                };
        }
    }
}
