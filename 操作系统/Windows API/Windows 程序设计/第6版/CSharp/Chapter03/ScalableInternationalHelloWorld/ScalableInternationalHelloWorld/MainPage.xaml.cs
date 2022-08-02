using Windows.Graphics.Display;
using Windows.UI.Xaml.Controls;

namespace ScalableInternationalHelloWorld
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
            SetFont();
            DisplayProperties.OrientationChanged += OnDisplayPropertiesOrientationChanged;
        }

        void OnDisplayPropertiesOrientationChanged(object sender)
        {
            SetFont();
        }

        void SetFont()
        {
            bool isLandscape = 
                DisplayProperties.CurrentOrientation == DisplayOrientations.Landscape ||
                DisplayProperties.CurrentOrientation == DisplayOrientations.LandscapeFlipped;

            this.FontSize = isLandscape ? 40 : 24;
        }
    }
}
