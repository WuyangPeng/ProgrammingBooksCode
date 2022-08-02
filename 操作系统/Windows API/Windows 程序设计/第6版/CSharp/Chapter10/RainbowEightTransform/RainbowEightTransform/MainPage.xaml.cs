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

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

namespace RainbowEightTransform
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();

            return;

            //Loaded += (sender, args) =>
            //    {
            //        double txtblkBaseSize = txtblk.ActualHeight;

            //        // Set FontSize as large as it can be
            //        txtblk.FontSize = this.ActualHeight / txtblkBaseSize;

            //        SizeChanged += (sizeSender, sizeArgs) =>
            //            {
            //                // Set FontSize as large as it can be
            //                txtblk.FontSize = this.ActualHeight / txtblkBaseSize;
            //            };
            //    };
        }
    }
}
