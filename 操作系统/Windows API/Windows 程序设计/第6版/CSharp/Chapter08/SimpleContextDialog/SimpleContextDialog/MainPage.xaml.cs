using System;
using Windows.Foundation;
using Windows.UI;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;

namespace SimpleContextDialog
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
        }

        void OnTextBlockRightTapped(object sender, RightTappedRoutedEventArgs args)
        {
            StackPanel stackPanel = new StackPanel();

            // Create two Button controls and add to StackPanel
            Button btn1 = new Button
            {
                Content = "Larger font",
                Tag = 1.2,
                HorizontalAlignment = HorizontalAlignment.Center,
                Margin = new Thickness(12)
            };
            btn1.Click += OnButtonClick;
            stackPanel.Children.Add(btn1);

            Button btn2 = new Button
            {
                Content = "Smaller font",
                Tag = 1 / 1.2,
                HorizontalAlignment = HorizontalAlignment.Center,
                Margin = new Thickness(12)
            };
            btn2.Click += OnButtonClick;
            stackPanel.Children.Add(btn2);

            // Create three RadioButton controls and add to StackPanel
            string[] names = { "Red", "Green", "Blue" };
            Color[] colors = { Colors.Red, Colors.Green, Colors.Blue };

            for (int i = 0; i < names.Length; i++)
            {
                RadioButton radioButton = new RadioButton
                {
                    Content = names[i],
                    Foreground = new SolidColorBrush(colors[i]),
                    IsChecked = (textBlock.Foreground as SolidColorBrush).Color == colors[i],
                    Margin = new Thickness(12)
                };
                radioButton.Checked += OnRadioButtonChecked;
                stackPanel.Children.Add(radioButton);
            }

            // Create a Border for the StackPanel
            Border border = new Border
            {
                Child = stackPanel,
                Background = this.Resources["ApplicationPageBackgroundThemeBrush"] as SolidColorBrush,
                BorderBrush = this.Resources["ApplicationForegroundThemeBrush"] as SolidColorBrush,
                BorderThickness = new Thickness(1),
                Padding = new Thickness(24),
            };

            // Create the Popup object
            Popup popup = new Popup
            {
                Child = border,
                IsLightDismissEnabled = true
            };

            // Adjust location based on content size
            border.Loaded += (loadedSender, loadedArgs) =>
                {
                    // Get an initial upper-left position
                    Point point = args.GetPosition(this);
                    point.X -= border.ActualWidth / 2;
                    point.Y -= border.ActualHeight;

                    // Leave at least a quarter inch margin
                    popup.HorizontalOffset = 
                        Math.Min(this.ActualWidth - border.ActualWidth - 24, 
                            Math.Max(24, point.X));

                    popup.VerticalOffset = 
                        Math.Min(this.ActualHeight - border.ActualHeight - 24,
                            Math.Max(24, point.Y));

                    // Set keyboard focus to first element
                    btn1.Focus(FocusState.Programmatic);
                };

            // Open the popup
            popup.IsOpen = true;
        }

        void OnButtonClick(object sender, RoutedEventArgs args)
        {
            textBlock.FontSize *= (double)(sender as Button).Tag;
        }

        void OnRadioButtonChecked(object sender, RoutedEventArgs args)
        {
            textBlock.Foreground = (sender as RadioButton).Foreground;
        }
    }
}
