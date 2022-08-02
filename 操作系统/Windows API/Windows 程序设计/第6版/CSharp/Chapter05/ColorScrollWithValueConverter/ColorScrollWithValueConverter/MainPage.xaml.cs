using Windows.UI;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;

namespace ColorScrollWithValueConverter
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
        }

        void OnSliderValueChanged(object sender, RangeBaseValueChangedEventArgs args)
        {
            byte r = (byte)redSlider.Value;
            byte g = (byte)greenSlider.Value;
            byte b = (byte)blueSlider.Value;

            brushResult.Color = Color.FromArgb(255, r, g, b);
        }
    }
}
