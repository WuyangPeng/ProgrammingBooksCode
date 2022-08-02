using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;

namespace FingerPaint
{
    public sealed partial class AboutBox : UserControl
    {
        public AboutBox()
        {
            this.InitializeComponent();
        }

        void OnBackButtonClick(object sender, RoutedEventArgs args)
        {
            // Dismiss Popup
            Popup popup = this.Parent as Popup;

            if (popup != null)
                popup.IsOpen = false;
        }
    }
}
