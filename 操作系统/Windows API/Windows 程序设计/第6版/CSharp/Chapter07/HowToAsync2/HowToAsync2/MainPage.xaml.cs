using Windows.Foundation;
using Windows.UI;
using Windows.UI.Core;
using Windows.UI.Popups;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;

namespace HowToAsync2
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
        }

        void OnButtonClick(object sender, RoutedEventArgs args)
        {
            MessageDialog msgdlg = new MessageDialog("Choose a color", "How To Async #2");
            msgdlg.Commands.Add(new UICommand("Red", null, Colors.Red));
            msgdlg.Commands.Add(new UICommand("Green", null, Colors.Green));
            msgdlg.Commands.Add(new UICommand("Blue", null, Colors.Blue));

            // Show the MessageDialog with a Completed handler
            IAsyncOperation<IUICommand> asyncOp = msgdlg.ShowAsync();
            asyncOp.Completed = (asyncInfo, asyncStatus) =>
                {
                    // Get the Color value
                    IUICommand command = asyncInfo.GetResults();
                    Color clr = (Color)command.Id;

                    // Use a Dispatcher to run in the UI thread
                    IAsyncAction asyncAction = this.Dispatcher.RunAsync(CoreDispatcherPriority.Normal, 
                                                                        () =>
                        {
                            // Set the background brush
                            contentGrid.Background = new SolidColorBrush(clr);
                        });
                };
        }
    }
}
