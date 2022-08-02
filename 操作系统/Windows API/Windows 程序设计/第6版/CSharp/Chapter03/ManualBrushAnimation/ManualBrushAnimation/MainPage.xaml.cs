using Windows.UI;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;

namespace ManualBrushAnimation
{
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
            CompositionTarget.Rendering += OnCompositionTargetRendering;
        }

        void OnCompositionTargetRendering(object sender, object args)
        {
            RenderingEventArgs renderingArgs = args as RenderingEventArgs;
            double t = (0.25 * renderingArgs.RenderingTime.TotalSeconds) % 1;
            t = t < 0.5 ? 2 * t : 2 - 2 * t;

            // Background
            byte gray = (byte)(255 * t);
            Color clr = Color.FromArgb(255, gray, gray, gray);
            contentGrid.Background = new SolidColorBrush(clr);

            // Foreground
            gray = (byte)(255 - gray);
            clr = Color.FromArgb(255, gray, gray, gray);
            txtblk.Foreground = new SolidColorBrush(clr);
        }
    }
}
