using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media.Animation;

namespace ThreeDeeSpinningText
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
        }

        void OnBeginStopButton(object sender, RoutedEventArgs args)
        {
            Button btn = sender as Button;
            string key = GetSibling(btn, -1).Tag as string;
            Storyboard storyboard = this.Resources[key] as Storyboard;
            Button pauseResumeButton = GetSibling(btn, 1) as Button;
            pauseResumeButton.Content = "Pause";

            if (btn.Content as string == "Begin")
            {
                storyboard.Begin();
                btn.Content = "Stop";
                pauseResumeButton.IsEnabled = true;
            }
            else
            {
                storyboard.Stop();
                btn.Content = "Begin";
                pauseResumeButton.IsEnabled = false;
            }
        }

        void OnPauseResumeButton(object sender, RoutedEventArgs args)
        {
            Button btn = sender as Button;
            string key = GetSibling(btn, -2).Tag as string;
            Storyboard storyboard = this.Resources[key] as Storyboard;

            if (btn.Content as string == "Pause")
            {
                storyboard.Pause();
                btn.Content = "Resume";
            }
            else
            {
                storyboard.Resume();
                btn.Content = "Pause";
            }
        }

        FrameworkElement GetSibling(FrameworkElement element, int relativeIndex)
        {
            Panel parent = element.Parent as Panel;
            int index = parent.Children.IndexOf(element);
            return parent.Children[index + relativeIndex] as FrameworkElement;
        }
    }
}
