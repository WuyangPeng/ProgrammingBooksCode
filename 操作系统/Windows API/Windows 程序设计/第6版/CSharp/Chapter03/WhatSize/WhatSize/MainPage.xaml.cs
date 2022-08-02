using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace WhatSize
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
        }

        void OnPageSizeChanged(object sender, SizeChangedEventArgs args)
        {
            widthText.Text = args.NewSize.Width.ToString();
            heightText.Text = args.NewSize.Height.ToString();
        }
    }
}
