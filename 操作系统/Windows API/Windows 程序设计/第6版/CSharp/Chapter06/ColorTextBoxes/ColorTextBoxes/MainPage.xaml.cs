using Windows.UI.ViewManagement;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;

namespace ColorTextBoxes
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
            this.DataContext = new RgbViewModel();

            // Initialize to highlight color
            (this.DataContext as RgbViewModel).Color =
                        new UISettings().UIElementColor(UIElementType.Highlight);
        }
    }
}
