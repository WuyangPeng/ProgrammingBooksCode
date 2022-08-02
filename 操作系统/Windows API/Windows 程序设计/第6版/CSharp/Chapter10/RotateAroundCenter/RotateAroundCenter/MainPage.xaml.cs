using Windows.UI.Xaml.Controls;

namespace RotateAroundCenter
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();

            Loaded += (sender, args) =>
                {
                    rotate.CenterX = txtblk.ActualWidth / 2;
                };

            SizeChanged += (sender, args) =>
                {
                    rotate.CenterY = args.NewSize.Height / 2;
                };
        }
    }
}
