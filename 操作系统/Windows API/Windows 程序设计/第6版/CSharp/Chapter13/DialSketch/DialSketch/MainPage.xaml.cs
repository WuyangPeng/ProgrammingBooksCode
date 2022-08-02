using Windows.Foundation;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Media;

namespace DialSketch
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();

            Loaded += (sender, args) =>
                {
                    polyline.Points.Add(new Point(drawingGrid.ActualWidth / 2,
                                                  drawingGrid.ActualHeight / 2));
                };
        }

        void OnDialValueChanged(object sender, RangeBaseValueChangedEventArgs args)
        {
            Dial dial = sender as Dial;
            RotateTransform rotate = dial.RenderTransform as RotateTransform;
            rotate.Angle = args.NewValue;

            double xFraction = (horzDial.Value - horzDial.Minimum) / 
                                    (horzDial.Maximum - horzDial.Minimum);

            double yFraction = (vertDial.Value - vertDial.Minimum) / 
                                    (vertDial.Maximum - vertDial.Minimum);

            double x = xFraction * drawingGrid.ActualWidth;
            double y = yFraction * drawingGrid.ActualHeight;
            polyline.Points.Add(new Point(x, y));
        }

        void OnClearButtonClick(object sender, RoutedEventArgs args)
        {
            polyline.Points.Clear();
        }
    }
}
