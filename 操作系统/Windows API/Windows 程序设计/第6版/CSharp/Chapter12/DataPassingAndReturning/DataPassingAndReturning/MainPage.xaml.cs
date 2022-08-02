using Windows.UI;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

namespace DataPassingAndReturning
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
            this.NavigationCacheMode = NavigationCacheMode.Enabled;
        }

        protected override void OnNavigatedFrom(NavigationEventArgs args)
        {
            if (args.SourcePageType.Equals(typeof(DialogPage)))
                (args.Content as DialogPage).Completed += OnDialogPageCompleted;

            base.OnNavigatedFrom(args);
        }

        void OnGotoButtonClick(object sender, RoutedEventArgs args)
        {
            // Create PassData object
            PassData passData = new PassData();

            // Set the InitializeColor property from the RadioButton controls
            foreach (UIElement child in radioStack.Children)
                if ((child as RadioButton).IsChecked.Value)
                    passData.InitializeColor = (Color)(child as RadioButton).Tag;

            // Pass that object to Navigate
            this.Frame.Navigate(typeof(DialogPage), passData);
        }

        void OnDialogPageCompleted(object sender, ReturnData args)
        {
            // Set background from returned color
            contentGrid.Background = new SolidColorBrush(args.ReturnColor);

            // Set RadioButton for returned color
            foreach (UIElement child in radioStack.Children)
                if ((Color)(child as RadioButton).Tag == args.ReturnColor)
                    (child as RadioButton).IsChecked = true;

            (sender as DialogPage).Completed -= OnDialogPageCompleted;
        }
    }
}
