using System;
using Windows.UI;
using Windows.UI.Popups;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;

namespace HowToAsync3
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
        }

        async void OnButtonClick(object sender, RoutedEventArgs args)
        {
            MessageDialog msgdlg = new MessageDialog("Choose a color", "How To Async #3");
            msgdlg.Commands.Add(new UICommand("Red", null, Colors.Red));
            msgdlg.Commands.Add(new UICommand("Green", null, Colors.Green));
            msgdlg.Commands.Add(new UICommand("Blue", null, Colors.Blue));

            // Show the MessageDialog
            IUICommand command = await msgdlg.ShowAsync();

            // Get the Color value
            Color clr = (Color)command.Id;

            // Set the background brush
            contentGrid.Background = new SolidColorBrush(clr);
        }
    }
}
