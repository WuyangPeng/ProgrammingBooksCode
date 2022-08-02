using System;
using Windows.UI;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;

namespace Petzold.Windows8.Controls
{
    public sealed partial class ColorItem : UserControl
    {
        public ColorItem(string name, Color clr)
        {
            this.InitializeComponent();

            rectangle.Fill = new SolidColorBrush(clr);
            txtblkName.Text = name;
            txtblkRgb.Text = String.Format("{0:X2}-{1:X2}-{2:X2}-{3:X2}",
                                           clr.A, clr.R, clr.G, clr.B);
        }
    }
}
