using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace FastNotFluid
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
        }

        void OnCanvasSizeChanged(object sender, SizeChangedEventArgs args)
        {
            horzAnima.To = args.NewSize.Width;
            vertAnima.To = args.NewSize.Height;
        }
    }
}
