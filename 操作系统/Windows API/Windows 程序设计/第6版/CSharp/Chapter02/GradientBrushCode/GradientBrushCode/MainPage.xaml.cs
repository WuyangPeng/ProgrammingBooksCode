using Windows.Foundation;
using Windows.UI;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

namespace GradientBrushCode
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();

            // Create the foreground brush for the TextBlock
            LinearGradientBrush foregroundBrush = new LinearGradientBrush();
            foregroundBrush.StartPoint = new Point(0, 0);
            foregroundBrush.EndPoint = new Point(1, 0);

            GradientStop gradientStop = new GradientStop();
            gradientStop.Offset = 0;
            gradientStop.Color = Colors.Blue;
            foregroundBrush.GradientStops.Add(gradientStop);

            gradientStop = new GradientStop();
            gradientStop.Offset = 1;
            gradientStop.Color = Colors.Red;
            foregroundBrush.GradientStops.Add(gradientStop);

            txtblk.Foreground = foregroundBrush;

            // Create the background brush for the Grid
            LinearGradientBrush backgroundBrush = new LinearGradientBrush
            {
                 StartPoint = new Point(0, 0),
                 EndPoint = new Point(1, 0)
            };
            backgroundBrush.GradientStops.Add(new GradientStop 
            { 
                Offset = 0, 
                Color = Colors.Red 
            });
            backgroundBrush.GradientStops.Add(new GradientStop
            {
                Offset = 1,
                Color = Colors.Blue
            });

            contentGrid.Background = backgroundBrush;
        }
    }
}
