using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace UnconventionalAppBar
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
        }

        void OnAppBarButtonClick(object sender, RoutedEventArgs args)
        {
            textBlock.Foreground = (sender as Button).Foreground;
        }
    }
}
