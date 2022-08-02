using System;
using Windows.UI;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;

namespace ManualColorAnimation
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
            gridBrush.Color = Color.FromArgb(255, gray, gray, gray);

            // Foreground
            gray = (byte)(255 - gray);
            txtblkBrush.Color = Color.FromArgb(255, gray, gray, gray);
        }
    }
}
