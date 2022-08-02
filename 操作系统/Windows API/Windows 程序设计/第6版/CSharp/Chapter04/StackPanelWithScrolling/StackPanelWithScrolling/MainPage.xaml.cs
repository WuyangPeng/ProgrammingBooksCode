using System;
using System.Collections.Generic;
using System.Reflection;                // GetTypeInfo, PropertyInfo
using Windows.UI;                       // Colors
using Windows.UI.Xaml.Controls;

namespace StackPanelWithScrolling
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();

            IEnumerable<PropertyInfo> properties =
                                    typeof(Colors).GetTypeInfo().DeclaredProperties;

            foreach (PropertyInfo property in properties)
            {
                Color clr = (Color)property.GetValue(null);
                TextBlock txtblk = new TextBlock();
                txtblk.Text = String.Format("{0} \x2014 {1:X2}-{2:X2}-{3:X2}-{4:X2}",
                                            property.Name, clr.A, clr.R, clr.G, clr.B);
                stackPanel.Children.Add(txtblk);
            }
        }
    }
}
