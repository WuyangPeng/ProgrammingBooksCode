using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media.Animation;

namespace JiggleButtonDemo
{
    public sealed partial class JiggleButton : Button
    {
        public JiggleButton()
        {
            this.InitializeComponent();
        }

        void OnJiggleButtonClick(object sender, RoutedEventArgs args)
        {
            (this.Resources["jiggleAnimation"] as Storyboard).Begin();
        }
    }
}
