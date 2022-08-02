using System;
using System.Collections.Generic;
using Windows.Foundation;
using Windows.System;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Shapes;

namespace Whirligig
{
    public sealed partial class MainPage : Page
    {
        const double Radius = 24;           // 1/4 inch
        const double AngleIncrement = 0.5;  // radians per pixel

        class TouchInfo
        {
            public Point LastPoint;
            public Polyline Polyline;
            public double Angle;
        }

        Dictionary<uint, TouchInfo> pointerDictionary = new Dictionary<uint, TouchInfo>();

        public MainPage()
        {
            this.InitializeComponent();
        }

        protected override void OnPointerPressed(PointerRoutedEventArgs args)
        {
            // Get information from event arguments
            uint id = args.Pointer.PointerId;
            Point point = args.GetCurrentPoint(this).Position;

            // Create Polyline
            Polyline polyline = new Polyline
            {
                Stroke = this.Resources["ApplicationForegroundThemeBrush"] as Brush,
                StrokeThickness = 1,
            };

            // Add to Grid
            contentGrid.Children.Add(polyline);

            // Create TouchInfo
            TouchInfo touchInfo = new TouchInfo
            {
                LastPoint = point,
                Polyline = polyline
            };

            // Add to dictionary
            pointerDictionary.Add(id, touchInfo);

            // Capture the Pointer
            CapturePointer(args.Pointer);
            base.OnPointerPressed(args);
        }

        protected override void OnPointerMoved(PointerRoutedEventArgs args)
        {
            // Get information from event arguments
            uint id = args.Pointer.PointerId;
            Point point = args.GetCurrentPoint(this).Position;

            // If ID is not in dictionary, don't do anything
            if (!pointerDictionary.ContainsKey(id))
                return;

            // Get TouchInfo objects
            Polyline polyline = pointerDictionary[id].Polyline;
            Point lastPoint = pointerDictionary[id].LastPoint;
            double angle = pointerDictionary[id].Angle;

            // Distance from last point to this point
            double distance = Math.Sqrt(Math.Pow(point.X - lastPoint.X, 2) +
                                        Math.Pow(point.Y - lastPoint.Y, 2));

            int divisions = (int)distance;

            for (int i = 0; i < divisions; i++)
            {
                // Sub-divide the distance between the last point and the new
                double x = (i * point.X + (divisions - i) * lastPoint.X) / divisions;
                double y = (i * point.Y + (divisions - i) * lastPoint.Y) / divisions;
                Point pt = new Point(x, y);

                // Increase the angle
                angle += distance * AngleIncrement / divisions;

                // Rotate the point
                pt.X += Radius * Math.Cos(angle);
                pt.Y += Radius * Math.Sin(angle);

                // Add to Polyline
                polyline.Points.Add(pt);
            }

            // Save new information
            pointerDictionary[id].LastPoint = point;
            pointerDictionary[id].Angle = angle;

            base.OnPointerMoved(args);
        }

        protected override void OnPointerReleased(PointerRoutedEventArgs args)
        {
            // Get information from event arguments
            uint id = args.Pointer.PointerId;

            // If ID is in dictionary, remove it
            if (pointerDictionary.ContainsKey(id))
                pointerDictionary.Remove(id);

            base.OnPointerReleased(args);
        }

        protected override void OnPointerCaptureLost(PointerRoutedEventArgs args)
        {
            // Get information from event arguments
            uint id = args.Pointer.PointerId;

            // If ID is in dictionary, abandon the drawing operation
            if (pointerDictionary.ContainsKey(id))
            {
                contentGrid.Children.Remove(pointerDictionary[id].Polyline);
                pointerDictionary.Remove(id);
            }

            base.OnPointerCaptureLost(args);
        }
    }
}
