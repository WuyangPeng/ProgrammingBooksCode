using System.Collections.Generic;
using System.Linq;
using Windows.Devices.Input;
using Windows.UI.Input;
using Windows.UI.Input.Inking;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Shapes;

namespace SimpleInking
{
    public sealed partial class MainPage : Page
    {
        InkManager inkManager = new InkManager();
        bool hasPen;

        public MainPage()
        {
            this.InitializeComponent();

            // Check if there's a pen among the pointer input devices
            foreach (PointerDevice device in PointerDevice.GetPointerDevices())
                hasPen |= device.PointerDeviceType == PointerDeviceType.Pen;
        }

        protected override void OnPointerPressed(PointerRoutedEventArgs args)
        {
            if (args.Pointer.PointerDeviceType == PointerDeviceType.Pen || !hasPen)
            {
                PointerPoint pointerPoint = args.GetCurrentPoint(this);
                inkManager.ProcessPointerDown(pointerPoint);
            }
            base.OnPointerPressed(args);
        }

        protected override void OnPointerMoved(PointerRoutedEventArgs args)
        {
            if ((args.Pointer.PointerDeviceType == PointerDeviceType.Pen || !hasPen) &&
                args.Pointer.IsInContact)
            {
                IEnumerable<PointerPoint> points = args.GetIntermediatePoints(this).Reverse();

                foreach (PointerPoint point in points)
                    inkManager.ProcessPointerUpdate(point);
            }
            base.OnPointerMoved(args);
        }

        protected override void OnPointerReleased(PointerRoutedEventArgs args)
        {
            if (args.Pointer.PointerDeviceType != PointerDeviceType.Pen && hasPen)
                return;

            inkManager.ProcessPointerUp(args.GetCurrentPoint(this));

            // Render the most recent InkStroke
            IReadOnlyList<InkStroke> inkStrokes = inkManager.GetStrokes();
            InkStroke inkStroke = inkStrokes[inkStrokes.Count - 1];

            // Create SolidColorBrush used for all segments in the stroke
            Brush brush = new SolidColorBrush(inkStroke.DrawingAttributes.Color);

            // Get the segments
            IReadOnlyList<InkStrokeRenderingSegment> inkSegments = inkStroke.GetRenderingSegments();

            // Notice loop starts at 1
            for (int i = 1; i < inkSegments.Count; i++)
            {
                InkStrokeRenderingSegment inkSegment = inkSegments[i];

                // Create a BezierSegment from the points
                BezierSegment bezierSegment = new BezierSegment
                {
                    Point1 = inkSegment.BezierControlPoint1,
                    Point2 = inkSegment.BezierControlPoint2,
                    Point3 = inkSegment.Position
                };

                // Create a PathFigure that begins at the preceding Position
                PathFigure pathFigure = new PathFigure
                {
                    StartPoint = inkSegments[i - 1].Position,
                    IsClosed = false,
                    IsFilled = false
                };
                pathFigure.Segments.Add(bezierSegment);

                // Create a PathGeometry with that PathFigure
                PathGeometry pathGeometry = new PathGeometry();
                pathGeometry.Figures.Add(pathFigure);

                // Create a Path with that PathGeometry
                Path path = new Path
                {
                    Stroke = brush,
                    StrokeThickness = inkStroke.DrawingAttributes.Size.Width * 
                                      inkSegment.Pressure,
                    StrokeStartLineCap = PenLineCap.Round,
                    StrokeEndLineCap = PenLineCap.Round,
                    Data = pathGeometry
                };

                // Add it to the Grid
                contentGrid.Children.Add(path);
            }
            base.OnPointerReleased(args);
        }
    }
}
