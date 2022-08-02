using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media.Animation;

namespace PreconfiguredAnimations
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
        }

        void OnButtonClick(object sender, RoutedEventArgs args)
        {
            Button btn = sender as Button;
            string key = btn.Tag as string;
            Storyboard storyboard = this.Resources[key] as Storyboard;
            storyboard.Begin();
        }
    }
}
