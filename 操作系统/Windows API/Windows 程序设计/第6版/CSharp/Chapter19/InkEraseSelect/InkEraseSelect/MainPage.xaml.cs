using System.Collections.Generic;
using System.Linq;
using Windows.ApplicationModel.DataTransfer;
using Windows.Devices.Input;
using Windows.Foundation;
using Windows.UI;
using Windows.UI.Input;
using Windows.UI.Input.Inking;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Shapes;

namespace InkEraseSelect
{
    public sealed partial class MainPage : Page
    {
        InkManager inkManager = new InkManager();
        InkDrawingAttributes inkDrawingAttributes = new InkDrawingAttributes();
        bool hasPen;

        Dictionary<uint, Point> pointerDictionary = new Dictionary<uint, Point>();
        Brush selectionBrush = new SolidColorBrush(Colors.Red);

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

                // Initialize for erasing, selecting, or inking
                if (pointerPoint.Properties.IsEraser)
                {
                    inkManager.Mode = InkManipulationMode.Erasing;
                }
                else if (pointerPoint.Properties.IsBarrelButtonPressed)
                {
                    inkManager.Mode = InkManipulationMode.Selecting;

                    // Create Polyline for showing enclosure
                    Polyline polyline = new Polyline
                    {
                        Stroke = selectionBrush,
                        StrokeThickness = 1
                    };
                    polyline.Points.Add(pointerPoint.Position);
                    newLineGrid.Children.Add(polyline);
                }
                else
                {
                    inkManager.Mode = InkManipulationMode.Inking;
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
                    Point point1 = pointerDictionary[id];
                    Point point2 = pointerPoint.Position;

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
                    else if (inkManager.Mode == InkManipulationMode.Selecting)
                    {
                        Polyline polyline = newLineGrid.Children[0] as Polyline;
                        polyline.Points.Add(point2);
                    }
                    else // inkManager.Mode == InkManipulationMode.Inking
                    {
                        // Render the line
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
                    }
                    pointerDictionary[id] = point2;
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
                    // Get rid of the little line segments
                    newLineGrid.Children.Clear();

                    // Render the new stroke
                    IReadOnlyList<InkStroke> inkStrokes = inkManager.GetStrokes();
                    InkStroke inkStroke = inkStrokes[inkStrokes.Count - 1];
                    RenderStroke(inkStroke);
                }
                else if (inkManager.Mode == InkManipulationMode.Selecting)
                {
                    // Get rid of the enclosure line
                    newLineGrid.Children.Clear();

                    // Render everything so selected items are identified
                    RenderAll();
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
            Color color = inkStroke.DrawingAttributes.Color;
            double penSize = inkStroke.DrawingAttributes.Size.Width;

            if (inkStroke.Selected)
                RenderBeziers(contentGrid, inkStroke, Colors.Silver, penSize + 24);

            RenderBeziers(contentGrid, inkStroke, color, penSize);
        }

        static void RenderBeziers(Panel panel, InkStroke inkStroke, Color color, double penSize)
        {
            Brush brush = new SolidColorBrush(color);
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
                    StrokeThickness = penSize * inkSegment.Pressure,
                    StrokeStartLineCap = PenLineCap.Round,
                    StrokeEndLineCap = PenLineCap.Round,
                    Data = pathGeometry
                };
                panel.Children.Add(path);
            }
        }

        void OnAppBarOpened(object sender, object args)
        {
            bool isAnythingSelected = false;

            foreach (InkStroke inkStroke in inkManager.GetStrokes())
                isAnythingSelected |= inkStroke.Selected;

            copyAppBarButton.IsEnabled = isAnythingSelected;
            cutAppBarButton.IsEnabled = isAnythingSelected;
            pasteAppBarButton.IsEnabled = inkManager.CanPasteFromClipboard();
            deleteAppBarButton.IsEnabled = isAnythingSelected;
        }

        void OnCopyAppBarButtonClick(object sender, RoutedEventArgs args)
        {
            inkManager.CopySelectedToClipboard();

            foreach (InkStroke inkStroke in inkManager.GetStrokes())
                inkStroke.Selected = false;

            RenderAll();
            bottomAppBar.IsOpen = false;
        }

        void OnCutAppBarButtonClick(object sender, RoutedEventArgs args)
        {
            inkManager.CopySelectedToClipboard();
            inkManager.DeleteSelected();
            RenderAll();
            bottomAppBar.IsOpen = false;
        }

        void OnPasteAppBarButtonClick(object sender, RoutedEventArgs args)
        {
            inkManager.PasteFromClipboard(new Point());
            RenderAll();
            bottomAppBar.IsOpen = false;
        }

        void OnDeleteAppBarButtonClick(object sender, RoutedEventArgs args)
        {
            inkManager.DeleteSelected();
            RenderAll();
            bottomAppBar.IsOpen = false;
        }
    }
}