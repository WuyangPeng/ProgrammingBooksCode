using System.Collections.Generic;
using System.Linq;
using Windows.Devices.Input;
using Windows.Foundation;
using Windows.UI;
using Windows.UI.Input;
using Windows.UI.Input.Inking;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Shapes;

namespace InkAndErase
{
    public sealed partial class MainPage : Page
    {
        InkManager inkManager = new InkManager();
        InkDrawingAttributes inkDrawingAttributes = new InkDrawingAttributes();
        bool hasPen;

        Dictionary<uint, Point> pointerDictionary = new Dictionary<uint, Point>();

        public MainPage()
        {
            this.InitializeComponent();

            // Check if there's a pen among the pointer input devices
            foreach (PointerDevice device in PointerDevice.GetPointerDevices())
                hasPen |= device.PointerDeviceType == PointerDeviceType.Pen;

            // Default drawing attributes
            inkDrawingAttributes.Color = Colors.Blue;
            inkDrawingAttributes.Size = new Size(6, 6);
            inkManager.SetDefaultDrawingAttributes(inkDrawingAttributes);
        }

        protected override void OnPointerPressed(PointerRoutedEventArgs args)
        {
            if (args.Pointer.PointerDeviceType == PointerDeviceType.Pen || !hasPen)
            {
                // Get information
                PointerPoint pointerPoint = args.GetCurrentPoint(this);
                uint id = pointerPoint.PointerId;

                // Initialize for inking or erasing
                if (!pointerPoint.Properties.IsEraser)
                {
                    inkManager.Mode = InkManipulationMode.Inking;
                }
                else
                {
                    inkManager.Mode = InkManipulationMode.Erasing;
                }

                // Give PointerPoint to InkManager
                inkManager.ProcessPointerDown(pointerPoint);

                // Add an entry to the dictionary
                pointerDictionary.Add(args.Pointer.PointerId, pointerPoint.Position);

                // Capture the pointer
                CapturePointer(args.Pointer);
            }
            base.OnPointerPressed(args);
        }

        protected override void OnPointerMoved(PointerRoutedEventArgs args)
        {
            // Get information
            PointerPoint pointerPoint = args.GetCurrentPoint(this);
            uint id = pointerPoint.PointerId;

            if (pointerDictionary.ContainsKey(id))
            {
                foreach (PointerPoint point in args.GetIntermediatePoints(this).Reverse())
                {
                    // Give PointerPoint to InkManager
                    object obj = inkManager.ProcessPointerUpdate(point);

                    if (inkManager.Mode == InkManipulationMode.Erasing)
                    {
                        // See if something has actually been removed
                        Rect rect = (Rect)obj;

                        if (rect.Width != 0 && rect.Height != 0)
                        {
                            RenderAll();
                        }
                    }
                    else
                    {
                        // Render the line
                        Point point1 = pointerDictionary[id];
                        Point point2 = pointerPoint.Position;

                        Line line = new Line
                        {
                            X1 = point1.X,
                            Y1 = point1.Y,
                            X2 = point2.X,
                            Y2 = point2.Y,
                            Stroke = new SolidColorBrush(inkDrawingAttributes.Color),
                            StrokeThickness = inkDrawingAttributes.Size.Width * 
                                              pointerPoint.Properties.Pressure,
                            StrokeStartLineCap = PenLineCap.Round,
                            StrokeEndLineCap = PenLineCap.Round
                        };
                        newLineGrid.Children.Add(line);
                        pointerDictionary[id] = point2;
                    }
                }
            }
            base.OnPointerMoved(args);
        }

        protected override void OnPointerReleased(PointerRoutedEventArgs args)
        {
            // Get information
            PointerPoint pointerPoint = args.GetCurrentPoint(this);
            uint id = pointerPoint.PointerId;

            if (pointerDictionary.ContainsKey(id))
            {
                // Give PointerPoint to InkManager
                inkManager.ProcessPointerUp(pointerPoint);

                if (inkManager.Mode == InkManipulationMode.Inking)
                {
                    // Get rid of the little Line segments
                    newLineGrid.Children.Clear();

                    // Render the new stroke
                    IReadOnlyList<InkStroke> inkStrokes = inkManager.GetStrokes();
                    InkStroke inkStroke = inkStrokes[inkStrokes.Count - 1];
                    RenderStroke(inkStroke);
                }
                pointerDictionary.Remove(id);
            }
            base.OnPointerReleased(args);
        }

        protected override void OnPointerCaptureLost(PointerRoutedEventArgs args)
        {
            uint id = args.Pointer.PointerId;

            if (pointerDictionary.ContainsKey(id))
            {
                pointerDictionary.Remove(id);
                newLineGrid.Children.Clear();
                RenderAll();
            }
            base.OnPointerCaptureLost(args);
        }

        void RenderAll()
        {
            contentGrid.Children.Clear();

            foreach (InkStroke inkStroke in inkManager.GetStrokes())
                RenderStroke(inkStroke);
        }

        void RenderStroke(InkStroke inkStroke)
        {
            Brush brush = new SolidColorBrush(inkStroke.DrawingAttributes.Color);
            IReadOnlyList<InkStrokeRenderingSegment> inkSegments = inkStroke.GetRenderingSegments();

            for (int i = 1; i < inkSegments.Count; i++)
            {
                InkStrokeRenderingSegment inkSegment = inkSegments[i];

                BezierSegment bezierSegment = new BezierSegment
                {
                    Point1 = inkSegment.BezierControlPoint1,
                    Point2 = inkSegment.BezierControlPoint2,
                    Point3 = inkSegment.Position
                };

                PathFigure pathFigure = new PathFigure
                {
                    StartPoint = inkSegments[i - 1].Position,
                    IsClosed = false,
                    IsFilled = false
                };
                pathFigure.Segments.Add(bezierSegment);

                PathGeometry pathGeometry = new PathGeometry();
                pathGeometry.Figures.Add(pathFigure);

                Path path = new Path
                {
                    Stroke = brush,
                    StrokeThickness = inkStroke.DrawingAttributes.Size.Width * 
                                      inkSegment.Pressure,
                    StrokeStartLineCap = PenLineCap.Round,
                    StrokeEndLineCap = PenLineCap.Round,
                    Data = pathGeometry
                };
                contentGrid.Children.Add(path);
            }
        }
    }
}