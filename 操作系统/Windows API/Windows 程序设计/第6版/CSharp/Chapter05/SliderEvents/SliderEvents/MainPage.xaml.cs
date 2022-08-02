using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;

namespace SliderEvents
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
        }

        void OnSliderValueChanged(object sender, RangeBaseValueChangedEventArgs args)
        {
            Slider slider = sender as Slider;
            Panel parentPanel = slider.Parent as Panel;
            int childIndex = parentPanel.Children.IndexOf(slider);
            TextBlock txtblk = parentPanel.Children[childIndex + 1] as TextBlock;
            txtblk.Text = args.NewValue.ToString();
        }
    }
}
