using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

namespace RotationCenterDemo
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();

            Loaded += (sender, args) =>
                {
                    translateBack1.X =
                    translateBack2.X =
                    translateBack3.X = -(translate.X = txtblk.ActualWidth / 2);

                    translateBack1.Y =
                    translateBack2.Y =
                    translateBack3.Y = -(translate.Y = txtblk.ActualHeight / 2);
                };
        }
    }
}
