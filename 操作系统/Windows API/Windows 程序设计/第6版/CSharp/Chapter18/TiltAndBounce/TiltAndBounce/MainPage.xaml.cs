using System;
using Windows.Devices.Sensors;
using Windows.Foundation;
using Windows.Graphics.Display;
using Windows.UI.Popups;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;

using Petzold.Windows8.VectorDrawing;

namespace TiltAndBounce
{
    public sealed partial class MainPage : Page
    {
        const double GRAVITY = 5000;    // pixels per second squared
        const double BALL_RADIUS = 32;
        const double BOUNCE = -2.0 / 3; // fraction of velocity

        Accelerometer accelerometer = Accelerometer.GetDefault();
        TimeSpan timeSpan;
        Vector2 acceleration;
        Vector2 ballPosition;
        Vector2 ballVelocity;

        public MainPage()
        {
            this.InitializeComponent();
            DisplayProperties.AutoRotationPreferences = DisplayProperties.NativeOrientation;

            ball.RadiusX = BALL_RADIUS;
            ball.RadiusY = BALL_RADIUS;

            Loaded += OnMainPageLoaded;
        }

        async void OnMainPageLoaded(object sender, RoutedEventArgs args)
        {
            if (accelerometer == null)
            {
                await new MessageDialog("Accelerometer is not available").ShowAsync();
            }
            else
            {
                CompositionTarget.Rendering += OnCompositionTargetRendering;
            }
        } 

        void OnCompositionTargetRendering(object sender, object args)
        {
            AccelerometerReading reading = accelerometer.GetCurrentReading();

            if (reading == null)
                return;

            // Get elapsed time
            TimeSpan timeSpan = (args as RenderingEventArgs).RenderingTime;
            double elapsedSeconds = (timeSpan - this.timeSpan).TotalSeconds;
            this.timeSpan = timeSpan;

            // Convert accelerometer reading to display coordinates
            double x = reading.AccelerationX;
            double y = -reading.AccelerationY;

            // Get current X-Y acceleration and smooth it
            acceleration = 0.5 * (acceleration + new Vector2(x, y));

            // Calculate new velocity and position
            ballVelocity += GRAVITY * acceleration * elapsedSeconds;
            ballPosition += ballVelocity * elapsedSeconds;

            // Check for bouncing off edge
            bool needAnotherLoop = true;

            while (needAnotherLoop)
            {
                needAnotherLoop = false;

                if (ballPosition.X - BALL_RADIUS < 0)
                {
                    ballPosition = new Vector2(-ballPosition.X + 2 * BALL_RADIUS, ballPosition.Y);
                    ballVelocity = new Vector2(BOUNCE * ballVelocity.X, ballVelocity.Y);
                    needAnotherLoop = true;
                }
                else if (ballPosition.X + BALL_RADIUS > this.ActualWidth)
                {
                    ballPosition = new Vector2(-ballPosition.X + 2 * (this.ActualWidth - BALL_RADIUS), 
                                               ballPosition.Y);
                    ballVelocity = new Vector2(BOUNCE * ballVelocity.X, ballVelocity.Y);
                    needAnotherLoop = true;
                }
                else if (ballPosition.Y - BALL_RADIUS < 0)
                {
                    ballPosition = new Vector2(ballPosition.X, -ballPosition.Y + 2 * BALL_RADIUS);
                    ballVelocity = new Vector2(ballVelocity.X, BOUNCE * ballVelocity.Y);
                    needAnotherLoop = true;
                }
                else if (ballPosition.Y + BALL_RADIUS > this.ActualHeight)
                {
                    ballPosition = new Vector2(ballPosition.X, 
                                               -ballPosition.Y + 2 * (this.ActualHeight - BALL_RADIUS));
                    ballVelocity = new Vector2(ballVelocity.X, BOUNCE * ballVelocity.Y);
                    needAnotherLoop = true;
                }
            }
            ball.Center = new Point(ballPosition.X, ballPosition.Y);
        }
    }
}
