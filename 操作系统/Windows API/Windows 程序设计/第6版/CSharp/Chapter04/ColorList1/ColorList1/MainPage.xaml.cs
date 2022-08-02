using System;
using System.Collections.Generic;
using System.Reflection;                    // for TypeInfo etc.
using Windows.UI;                           // for Colors
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Shapes;               // for Rectangle

namespace ColorList1
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();

            IEnumerable<PropertyInfo> properties = typeof(Colors).GetTypeInfo().DeclaredProperties;

            foreach (PropertyInfo property in properties)
            {
                Color clr = (Color)property.GetValue(null);

                StackPanel vertStackPanel = new StackPanel
                {
                    VerticalAlignment = VerticalAlignment.Center
                };

                TextBlock txtblkName = new TextBlock
                {
                    Text = property.Name,
                    FontSize = 24
                };
                vertStackPanel.Children.Add(txtblkName);

                TextBlock txtblkRgb = new TextBlock
                {
                    Text = String.Format("{0:X2}-{1:X2}-{2:X2}-{3:X2}", 
                                         clr.A, clr.R, clr.G, clr.B),
                    FontSize = 18
                };
                vertStackPanel.Children.Add(txtblkRgb);

                StackPanel horzStackPanel = new StackPanel
                {
                    Orientation = Orientation.Horizontal
                };

                Rectangle rectangle = new Rectangle
                {
                    Width = 72,
                    Height = 72,
                    Fill = new SolidColorBrush(clr),
                    Margin = new Thickness(6)
                };
                horzStackPanel.Children.Add(rectangle);
                horzStackPanel.Children.Add(vertStackPanel);
                stackPanel.Children.Add(horzStackPanel);
            }
        }
    }
}
