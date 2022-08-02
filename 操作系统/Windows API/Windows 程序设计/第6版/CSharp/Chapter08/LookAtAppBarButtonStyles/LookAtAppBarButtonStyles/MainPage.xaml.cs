using System;
using System.Collections.Generic;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Automation;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Media;

namespace LookAtAppBarButtonStyles
{
    public sealed partial class MainPage : Page
    {
        class Item
        {
            public string Key;
            public char Symbol;
            public string Text;
        }

        List<Item> appbarStyles = new List<Item>();
        FontFamily segoeSymbolFont = new FontFamily("Segoe UI Symbol");

        public MainPage()
        {
            this.InitializeComponent();
            Loaded += OnLoaded;
        }

        void OnLoaded(object sender, RoutedEventArgs args)
        {
            // Basically gets StandardStyles.xaml
            ResourceDictionary dictionary = Application.Current.Resources.MergedDictionaries[0];
            Style baseStyle = dictionary["AppBarButtonStyle"] as Style;

            // Find all styles based on AppBarButtonStyle
            foreach (object key in dictionary.Keys)
            {
                Style style = dictionary[key] as Style;

                if (style != null && style.BasedOn == baseStyle)
                {
                    Item item = new Item
                    {
                        Key = key as string
                    };

                    foreach (Setter setter in style.Setters)
                    {
                        if (setter.Property.Equals(AutomationProperties.NameProperty))
                            item.Text = setter.Value as string;

                        if (setter.Property.Equals(ButtonBase.ContentProperty))
                            item.Symbol = (setter.Value as string)[0];
                    }

                    appbarStyles.Add(item);
                }
            }

            // Display items by checking RadioButton
            symbolSortRadio.IsChecked = true;
        }

        void OnRadioButtonChecked(object sender, RoutedEventArgs args)
        {
            if (sender == symbolSortRadio)
            {
                // Sort by symbol
                appbarStyles.Sort((item1, item2) =>
                {
                    return item1.Symbol.CompareTo(item2.Symbol);
                });
            }
            else
            {
                // Sort by text
                appbarStyles.Sort((item1, item2) =>
                {
                    return item1.Text.CompareTo(item2.Text);
                });
            }

            // Close app bar and display the items
            this.BottomAppBar.IsOpen = false;
            DisplayList();
        }

        void DisplayList()
        {
            // Clear the StackPanel
            stackPanel.Children.Clear();

            // Loop through the styles
            foreach (Item item in appbarStyles)
            {
                // A StackPanel for each item
                StackPanel itemPanel = new StackPanel
                {
                    Orientation = Orientation.Horizontal,
                    Margin = new Thickness(0, 6, 0, 6)
                };

                // The symbol itself
                TextBlock textBlock = new TextBlock
                {
                    Text = item.Symbol.ToString(),
                    FontFamily = segoeSymbolFont,
                    Margin = new Thickness(24, 0, 24, 0)
                };
                itemPanel.Children.Add(textBlock);

                // The Unicode identifier
                textBlock = new TextBlock
                {
                    Text = "0x" + ((int)item.Symbol).ToString("X4"),
                    Width = 96
                };
                itemPanel.Children.Add(textBlock);

                // The text for the button
                textBlock = new TextBlock
                {
                    Text = "\"" + item.Text + "\"",
                    Width = 240,
                };
                itemPanel.Children.Add(textBlock);

                // The key name
                textBlock = new TextBlock
                {
                    Text = item.Key
                };
                itemPanel.Children.Add(textBlock);

                stackPanel.Children.Add(itemPanel);
            }
        }
    }
}