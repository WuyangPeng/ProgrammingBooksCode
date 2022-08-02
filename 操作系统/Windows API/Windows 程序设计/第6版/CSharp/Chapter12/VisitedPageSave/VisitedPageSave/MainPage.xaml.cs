using Windows.UI.Xaml;
using Windows.UI.Xaml.Navigation;

namespace VisitedPageSave
{
    public sealed partial class MainPage : SaveStatePage
    {
        public MainPage()
        {
            this.InitializeComponent();
        }

        protected override void OnNavigatedTo(NavigationEventArgs args)
        {
            // Enable buttons
            forwardButton.IsEnabled = this.Frame.CanGoForward;
            backButton.IsEnabled = this.Frame.CanGoBack;

            // Construct a dictionary key
            int pageKey = this.Frame.BackStackDepth;

            if (args.NavigationMode != NavigationMode.New)
            {
                // Get the page state dictionary for this page
                pageState = pages[pageKey];

                // Get the page state from the dictionary
                txtbox.Text = pageState["TextBoxText"] as string;
            }

            base.OnNavigatedTo(args);
        }

        protected override void OnNavigatedFrom(NavigationEventArgs args)
        {
            pageState.Clear();

            // Save the page state in the dictionary
            pageState.Add("TextBoxText", txtbox.Text);

            base.OnNavigatedFrom(args);
        }

        void OnGotoButtonClick(object sender, RoutedEventArgs args)
        {
            this.Frame.Navigate(typeof(SecondPage));
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
