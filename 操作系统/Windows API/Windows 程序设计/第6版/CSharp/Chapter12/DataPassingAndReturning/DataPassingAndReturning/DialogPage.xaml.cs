using System;
using Windows.UI;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Navigation;

namespace DataPassingAndReturning
{
    public sealed partial class DialogPage : Page
    {
        public event EventHandler<ReturnData> Completed;

        public DialogPage()
        {
            this.InitializeComponent();
        }

        protected override void OnNavigatedTo(NavigationEventArgs args)
        {
            // Get the object passed as the second argument to Navigate
            PassData passData = args.Parameter as PassData;

            // Use that to initialize the RadioButton controls
            foreach (UIElement child in radioStack.Children)
                if ((Color)(child as RadioButton).Tag == passData.InitializeColor)
                    (child as RadioButton).IsChecked = true;

            base.OnNavigatedTo(args);
        }

        protected override void OnNavigatedFrom(NavigationEventArgs args)
        {
            if (Completed != null)
            {
                // Create ReturnData object
                ReturnData returnData = new ReturnData();

                // Set the ReturnColor property from the RadioButton controls
                foreach (UIElement child in radioStack.Children)
                    if ((child as RadioButton).IsChecked.Value)
                        returnData.ReturnColor = (Color)(child as RadioButton).Tag;

                // Fire the Completed event
                Completed(this, returnData);
            }

            base.OnNavigatedFrom(args);
        }

        void OnReturnButtonClick(object sender, RoutedEventArgs args)
        {
            this.Frame.GoBack();
        }
    }
}
