using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace RadialGradientBrushDemo
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
        }

        void OnCanvasSizeChanged(object sender, SizeChangedEventArgs args)
        {
            // Canvas.Left animation
            leftAnima.To = args.NewSize.Width;

            // Canvas.Top animation
            rightAnima.To = args.NewSize.Height;
        }
    }
}
