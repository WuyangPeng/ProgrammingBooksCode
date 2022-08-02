using Windows.UI;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;

namespace OrientableColorScroll
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

            redValue.Text = r.ToString("X2");
            greenValue.Text = g.ToString("X2");
            blueValue.Text = b.ToString("X2");

            brushResult.Color = Color.FromArgb(255, r, g, b);
        }

        void OnGridSizeChanged(object sender, SizeChangedEventArgs args)
        {
            // Landscape mode
            if (args.NewSize.Width > args.NewSize.Height)
            {
                secondColDef.Width = new GridLength(1, GridUnitType.Star);
                secondRowDef.Height = new GridLength(0);

                Grid.SetColumn(rectangleResult, 1);
                Grid.SetRow(rectangleResult, 0);
            }
            // Portrait mode
            else
            {
                secondColDef.Width = new GridLength(0);
                secondRowDef.Height = new GridLength(1, GridUnitType.Star);

                Grid.SetColumn(rectangleResult, 0);
                Grid.SetRow(rectangleResult, 1);
            }
        }
    }
}
