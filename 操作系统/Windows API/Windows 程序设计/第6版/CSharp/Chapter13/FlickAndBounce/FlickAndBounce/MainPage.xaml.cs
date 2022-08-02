using System;
using Windows.Foundation;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Input;

namespace FlickAndBounce
{
    public sealed partial class MainPage : Page
    {
        int xDirection;
        int yDirection;

        public MainPage()
        {
            this.InitializeComponent();
        }

        void OnEllipseManipulationStarted(object sender, ManipulationStartedRoutedEventArgs args)
        {
            // Initialize directions
            xDirection = 1;
            yDirection = 1;
        }

        void OnEllipseManipulationDelta(object sender, ManipulationDeltaRoutedEventArgs args)
        {
            // Find new position of ellipse regardless of edges
            double x = Canvas.GetLeft(ellipse) + xDirection * args.Delta.Translation.X;
            double y = Canvas.GetTop(ellipse) + yDirection * args.Delta.Translation.Y;

            if (args.IsInertial)
            {
                // Bounce it off the edges
                Size playground = new Size(contentGrid.ActualWidth - ellipse.Width,
                                           contentGrid.ActualHeight - ellipse.Height);

                while (x < 0 || y < 0 || x > playground.Width || y > playground.Height)
                {
                    if (x < 0)
                    {
                        x = -x;
                        xDirection *= -1;
                    }
                    if (x > playground.Width)
                    {
                        x = 2 * playground.Width - x;
                        xDirection *= -1;
                    }
                    if (y < 0)
                    {
                        y = -y;
                        yDirection *= -1;
                    }
                    if (y > playground.Height)
                    {
                        y = 2 * playground.Height - y;
                        yDirection *= -1;
                    }
                }
            }

            Canvas.SetLeft(ellipse, x);
            Canvas.SetTop(ellipse, y);
        }

        void OnEllipseManipulationInertiaStarting(object sender, 
                                                  ManipulationInertiaStartingRoutedEventArgs args)
        {
            double maxVelocity = Math.Max(Math.Abs(args.Velocities.Linear.X),
                                          Math.Abs(args.Velocities.Linear.Y));

            args.TranslationBehavior.DesiredDeceleration = maxVelocity / (1000 * slider.Value);
        }
    }
}
