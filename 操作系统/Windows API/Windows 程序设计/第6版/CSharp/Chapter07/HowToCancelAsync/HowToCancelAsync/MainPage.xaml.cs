using System;
using Windows.Foundation;
using Windows.UI;
using Windows.UI.Popups;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;

namespace HowToCancelAsync
{
    public sealed partial class MainPage : Page
    {
        IAsyncOperation<IUICommand> asyncOp;

        public MainPage()
        {
            this.InitializeComponent();
        }

        async void OnButtonClick(object sender, RoutedEventArgs args)
        {
            MessageDialog msgdlg = new MessageDialog("Choose a color", "How To Cancel Async");
            msgdlg.Commands.Add(new UICommand("Red", null, Colors.Red));
            msgdlg.Commands.Add(new UICommand("Green", null, Colors.Green));
            msgdlg.Commands.Add(new UICommand("Blue", null, Colors.Blue));

            // Start a five-second timer
            DispatcherTimer timer = new DispatcherTimer();
            timer.Interval = TimeSpan.FromSeconds(5);
            timer.Tick += OnTimerTick;
            timer.Start();

            // Show the MessageDialog
            asyncOp = msgdlg.ShowAsync();
            IUICommand command = null;

            try
            {
                command = await asyncOp;
            }
            catch (Exception)
            {
                // The exception in this case will be TaskCanceledException
            }

            // Stop the timer
            timer.Stop();

            // If the operation was cancelled, exit the method
            if (command == null)
                return;

            // Get the Color value and set the background brush
            Color clr = (Color)command.Id;
            contentGrid.Background = new SolidColorBrush(clr);
        }

        void OnTimerTick(object sender, object args)
        {
            // Cancel the asynchronous operation
            asyncOp.Cancel();
        }
    }
}
