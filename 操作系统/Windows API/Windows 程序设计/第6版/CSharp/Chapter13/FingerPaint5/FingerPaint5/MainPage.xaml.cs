using System;
using System.Collections.Generic;
using Windows.Foundation;
using Windows.UI;
using Windows.UI.Input;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Shapes;
using Petzold.Windows8.VectorDrawing;

namespace FingerPaint5
{
    public sealed partial class MainPage : Page
    {
        struct PointerInfo
        {
            public Brush Brush;
            public Point PreviousPoint;
            public double PreviousRadius;
        }

        Dictionary<uint, PointerInfo> pointerDictionary = new Dictionary<uint, PointerInfo>();
        Random rand = new Random();
        byte[] rgb = new byte[3];

        public MainPage()
        {
            this.InitializeComponent();
        }

        protected override void OnPointerPressed(PointerRoutedEventArgs args)
        {
            // Get information from event arguments
            uint id = args.Pointer.PointerId;
            PointerPoint pointerPoint = args.GetCurrentPoint(this);

            // Create random color
            rand.NextBytes(rgb);
            Color color = Color.FromArgb(255, rgb[0], rgb[1], rgb[2]);

            // Create PointerInfo
            PointerInfo pointerInfo = new PointerInfo
            {
                PreviousPoint = pointerPoint.Position,
                PreviousRadius = 24 * pointerPoint.Properties.Pressure,
                Brush = new SolidColorBrush(color)
            };

            // Add to dictionary
            pointerDictionary.Add(id, pointerInfo);

            // Capture the Pointer
            CapturePointer(args.Pointer);
            base.OnPointerPressed(args);
        }

        protected override void OnPointerMoved(PointerRoutedEventArgs args)
        {
            // Get ID from event arguments
            uint id = args.Pointer.PointerId;

            // If ID is in dictionary, start a loop
            if (pointerDictionary.ContainsKey(id))
            {
                PointerInfo pointerInfo = pointerDictionary[id];
                IList<PointerPoint> pointerpoints = args.GetIntermediatePoints(this);

                for (int i = pointerpoints.Count - 1; i >= 0; i--)
                {
                    PointerPoint pointerPoint = pointerpoints[i];

                    // For each point, create a Path element and add to Grid
                    Point point = pointerPoint.Position;
                    float pressure = pointerPoint.Properties.Pressure;
                    double radius = 24 * pressure;

                    Geometry geometry = 
                        CreateTaperedLineGeometry(pointerInfo.PreviousPoint,
                                                  pointerInfo.PreviousRadius,
                                                  point,
                                                  radius);
                    Path path = new Path
                    {
                        Data = geometry,
                        Fill = pointerInfo.Brush
                    };
                    contentGrid.Children.Add(path);

                    // Update PointerInfo
                    pointerInfo.PreviousPoint = point;
                    pointerInfo.PreviousRadius = radius;
                }
                // Store PointerInfo back in dictionary
                pointerDictionary[id] = pointerInfo;
            }
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

            // If ID is still in dictionary, remove it
            if (pointerDictionary.ContainsKey(id))
                pointerDictionary.Remove(id);

            base.OnPointerCaptureLost(args);
        }

        Geometry CreateTaperedLineGeometry(Point c0, double r0, Point c1, double r1)
        {
            // Swap the centers and radii so that c0 is 
            //      center of the the smaller circle.
            if (r1 < r0)
            {
                Point point = c0;
                c0 = c1;
                c1 = point;

                double radius = r0;
                r0 = r1;
                r1 = radius;
            }

            // Get vector from c1 to c0
            Vector2 vCenters = new Vector2(c0) - new Vector2(c1);

            // Get length and normalized version
            double d = vCenters.Length;
            vCenters = vCenters.Normalized;

            // Determine if one circle is enclosed in the other
            bool enclosed = r0 + d < r1;

            // Define tangent points derived in both algorithms
            Point t0R = new Point();
            Point t0L = new Point();
            Point t1R = new Point();
            Point t1L = new Point();
             
            // Case for two circles of same size
            if (r0 == r1 || enclosed)
            {
                // Rotate centers vector 90 degrees
                Vector2 vLeft = new Vector2(-vCenters.Y, vCenters.X);
                
                // Rotate -90 degrees
                Vector2 vRight = -vLeft;

                // Find tangent points
                t0R = c0 + r0 * vRight;
                t0L = c0 + r0 * vLeft;
                t1R = c1 + r1 * vRight;
                t1L = c1 + r1 * vLeft;
            }
            // A bit more difficult for two circles of unequal size
            else
            {
                // Create focal point F extending from c0
                double e = d * r0 / (r1 - r0);
                Point F = c0 + e * vCenters;

                // Find angle and length of right-triangle legs
                double alpha = 180 * Math.Asin(r0 / e) / Math.PI;
                double leg0 = Math.Sqrt(e * e - r0 * r0);
                double leg1 = Math.Sqrt((e + d) * (e + d) - r1 * r1);

                // Vectors of tangent lines
                Vector2 vRight = -vCenters.Rotate(alpha);
                Vector2 vLeft = -vCenters.Rotate(-alpha);

                // Find tangent points
                t0R = F + leg0 * vRight;
                t0L = F + leg0 * vLeft;
                t1R = F + leg1 * vRight;
                t1L = F + leg1 * vLeft;
            }

            // Create PathGeometry with implied closing line
            PathGeometry pathGeometry = new PathGeometry();
            PathFigure pathFigure = new PathFigure
            {
                StartPoint = t0R,
                IsClosed = true,
                IsFilled = true
            };
            pathGeometry.Figures.Add(pathFigure);

            // Arc around smaller circle
            ArcSegment arc0Segment = new ArcSegment
            {
                Point = t0L,
                Size = new Size(r0, r0),
                SweepDirection = SweepDirection.Clockwise,
                IsLargeArc = false
            };
            pathFigure.Segments.Add(arc0Segment);

            // Line connecting smaller circle to larger circle
            LineSegment lineSegment = new LineSegment
            {
                Point = t1L
            };
            pathFigure.Segments.Add(lineSegment);

            // Arc around larger circle
            ArcSegment arc1Segment = new ArcSegment
            {
                Point = t1R,
                Size = new Size(r1, r1),
                SweepDirection = SweepDirection.Clockwise,
                IsLargeArc = true
            };
            pathFigure.Segments.Add(arc1Segment);

            return pathGeometry;
        }
    }
}
