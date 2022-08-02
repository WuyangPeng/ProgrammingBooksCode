using System;
using System.Collections.Generic;
using Windows.Foundation;
using Windows.UI;
using Windows.UI.ViewManagement;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Media.Imaging;
using DirectXWrapper;

namespace SpinPaint
{
    public sealed partial class MainPage : Page
    {
        class FingerInfo 
        {
            public Point LastPosition;
            public Point ThisPosition;
        }

        Dictionary<uint, FingerInfo> fingerTouches = new Dictionary<uint, FingerInfo>();

        int dimension;
        SurfaceImageSourceRenderer surfaceImageSourceRenderer;
        RotateTransform inverseRotate = new RotateTransform();

        public MainPage()
        {
            InitializeComponent();
            Loaded +=OnMainPageLoaded;
        }

        void OnMainPageLoaded(object sender, RoutedEventArgs args)
        {
            // Find the dimension of the square bitmap
            if (ApplicationView.Value == ApplicationViewState.FullScreenPortrait)
            {
                dimension = (int)(this.ActualWidth - referencePanel.Margin.Left 
                                                   - referencePanel.Margin.Right);
            }
            else
            {
                dimension = (int)(this.ActualHeight - referencePanel.Margin.Top 
                                                    - referencePanel.Margin.Bottom);
            }

            // Set this size to the reference panel so it doesn't get distorted in Snapped view
            referencePanel.Width = dimension;
            referencePanel.Height = dimension;

            // Create the SurfaceImageSource and renderer
            SurfaceImageSource surfaceImageSource = new SurfaceImageSource(dimension, dimension);
            surfaceImageSourceRenderer = new SurfaceImageSourceRenderer(surfaceImageSource, 
                                                                        dimension, dimension);
            image.Source = surfaceImageSource;

            // Set rotation centers
            rotate.CenterX = dimension / 2;
            rotate.CenterY = dimension / 2;

            inverseRotate.CenterX = dimension / 2;
            inverseRotate.CenterY = dimension / 2;

            // Start the event
            CompositionTarget.Rendering += OnCompositionTargetRendering;
        }

        protected override void OnPointerPressed(PointerRoutedEventArgs args)
        {
            uint id = args.Pointer.PointerId;
            Point pt = args.GetCurrentPoint(referencePanel).Position;

            if (fingerTouches.ContainsKey(id))
                fingerTouches.Remove(id);

            FingerInfo fingerInfo = new FingerInfo
            {
                LastPosition = new Point(Double.PositiveInfinity, Double.PositiveInfinity),
                ThisPosition = pt,
            };

            fingerTouches.Add(id, fingerInfo);
            CapturePointer(args.Pointer);
            base.OnPointerPressed(args);
        }

        protected override void OnPointerMoved(PointerRoutedEventArgs args)
        {
            uint id = args.Pointer.PointerId;
            Point pt = args.GetCurrentPoint(referencePanel).Position;

            if (fingerTouches.ContainsKey(id))
                fingerTouches[id].ThisPosition = pt;

            base.OnPointerMoved(args);
        }

        protected override void OnPointerReleased(PointerRoutedEventArgs args)
        {
            uint id = args.Pointer.PointerId;

            if (fingerTouches.ContainsKey(id))
                fingerTouches.Remove(id);

            base.OnPointerReleased(args);
        }

        protected override void OnPointerCaptureLost(PointerRoutedEventArgs args)
        {
            uint id = args.Pointer.PointerId;

            if (fingerTouches.ContainsKey(id))
                fingerTouches.Remove(id);

            base.OnPointerCaptureLost(args);
        }

        void OnCompositionTargetRendering(object sender, object args)
        {
            // Get elapsed seconds since app began
            TimeSpan timeSpan = (args as RenderingEventArgs).RenderingTime;
            double seconds = timeSpan.TotalSeconds;

            // Calculate rotation angle
            rotate.Angle = (360 * seconds / 5) % 360;

            // Calculate color and brush
            Color clr;
            double fraction = 6 * (seconds % 10) / 10;

            if (fraction < 1)
                clr = Color.FromArgb(255, 255, (byte)(fraction * 255), 0);
            else if (fraction < 2)
                clr = Color.FromArgb(255, (byte)(255 - (fraction - 1) * 255), 255, 0);
            else if (fraction < 3)
                clr = Color.FromArgb(255, 0, 255, (byte)((fraction - 2) * 255));
            else if (fraction < 4)
                clr = Color.FromArgb(255, 0, (byte)(255 - (fraction - 3) * 255), 255);
            else if (fraction < 5)
                clr = Color.FromArgb(255, (byte)((fraction - 4) * 255), 0, 255);
            else
                clr = Color.FromArgb(255, 255, 0, (byte)(255 - (fraction - 5) * 255));

            (pageTitle.Foreground as SolidColorBrush).Color = clr;

            // All done if nobody's touching
            if (fingerTouches.Count == 0)
                return;

            bool bitmapNeedsUpdate = false;

            foreach (FingerInfo fingerInfo in fingerTouches.Values)
            {
                // Find point relative to rotated bitmap
                inverseRotate.Angle = -rotate.Angle;
                Point point1 = inverseRotate.TransformPoint(fingerInfo.ThisPosition);

                if (!Double.IsPositiveInfinity(fingerInfo.LastPosition.X))
                {
                    Point point2 = fingerInfo.LastPosition;
                    float thickness = 12;

                    // Draw the lines
                    surfaceImageSourceRenderer.DrawLine(point1, point2, clr, thickness);
                    surfaceImageSourceRenderer.DrawLine(new Point(dimension - point1.X, point1.Y),
                                                        new Point(dimension - point2.X, point2.Y),
                                                        clr, thickness);
                    surfaceImageSourceRenderer.DrawLine(new Point(point1.X, dimension - point1.Y),
                                                        new Point(point2.X, dimension - point2.Y),
                                                        clr, thickness);
                    surfaceImageSourceRenderer.DrawLine(new Point(dimension - point1.X,
                                                                  dimension - point1.Y),
                                                        new Point(dimension - point2.X,
                                                                  dimension - point2.Y),
                                                        clr, thickness);
                    bitmapNeedsUpdate = true;
                }
                fingerInfo.LastPosition = point1;
            }

            // Update bitmap
            if (bitmapNeedsUpdate)
            {
                surfaceImageSourceRenderer.Update();
            }
        }

        void OnClearButtonClick(object sender, RoutedEventArgs e)
        {
            SurfaceImageSource surfaceImageSource = new SurfaceImageSource(dimension, dimension);
            surfaceImageSourceRenderer = new SurfaceImageSourceRenderer(surfaceImageSource, 
                                                                        dimension, dimension);
            image.Source = surfaceImageSource;
        }
    }
}
