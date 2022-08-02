using System;
using Windows.UI;
using Windows.UI.Popups;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;

namespace SimpleContextMenu
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
        }

        async void OnTextBlockRightTapped(object sender, RightTappedRoutedEventArgs args)
        {
            PopupMenu popupMenu = new PopupMenu();
            popupMenu.Commands.Add(new UICommand("Larger Font", OnFontSizeChanged, 1.2));
            popupMenu.Commands.Add(new UICommand("Smaller Font", OnFontSizeChanged, 1 / 1.2));
            popupMenu.Commands.Add(new UICommandSeparator());
            popupMenu.Commands.Add(new UICommand("Red", OnColorChanged, Colors.Red));
            popupMenu.Commands.Add(new UICommand("Green", OnColorChanged, Colors.Green));
            popupMenu.Commands.Add(new UICommand("Blue", OnColorChanged, Colors.Blue));

            await popupMenu.ShowAsync(args.GetPosition(this));
        }

        void OnFontSizeChanged(IUICommand command)
        {
            textBlock.FontSize *= (double)command.Id;
        }

        void OnColorChanged(IUICommand command)
        {
            textBlock.Foreground = new SolidColorBrush((Color)command.Id);
        }
    }
}
