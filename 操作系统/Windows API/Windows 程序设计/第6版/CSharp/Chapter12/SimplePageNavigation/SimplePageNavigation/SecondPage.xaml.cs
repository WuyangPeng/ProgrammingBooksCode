using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Navigation;

namespace SimplePageNavigation
{
    public sealed partial class SecondPage : Page
    {
        public SecondPage()
        {
            this.InitializeComponent();
        }

        protected override void OnNavigatedTo(NavigationEventArgs args)
        {
            forwardButton.IsEnabled = this.Frame.CanGoForward;
            backButton.IsEnabled = this.Frame.CanGoBack;
        }

        void OnGotoButtonClick(object sender, RoutedEventArgs args)
        {
            this.Frame.Navigate(typeof(MainPage));
        }

        void OnForwardButtonClick(object sender, RoutedEventArgs args)
        {
            this.Frame.GoForward();
        }

        void OnBackButtonClick(object sender, RoutedEventArgs args)
        {
            this.Frame.GoBack();
        }
    }
}
