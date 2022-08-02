using System;
using System.Collections.Generic;
using System.IO;
using Windows.Foundation;
using Windows.UI;
using Windows.UI.Input;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Petzold.Windows8.VectorDrawing;

namespace FingerPaint
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
        List<double> xCollection = new List<double>();

        protected override void OnPointerPressed(PointerRoutedEventArgs args)
        {
            // Get information from event arguments
            uint id = args.Pointer.PointerId;
            PointerPoint pointerPoint = args.GetCurrentPoint(this);

            // Create PointerInfo
            PointerInfo pointerInfo = new PointerInfo
            {
                PreviousPoint = pointerPoint.Position,
                PreviousRadius = appSettings.Thickness * pointerPoint.Properties.Pressure,
                Brush = new SolidColorBrush(appSettings.Color)
            };

            // Add to dictionary
            pointerDictionary.Add(id, pointerInfo);

            // Capture the Pointer
            CapturePointer(args.Pointer);

            base.OnPointerPressed(args);
        }

        protected override void OnPointerMoved(PointerRoutedEventArgs args)
        {
            // Get information from event arguments
            uint id = args.Pointer.PointerId;
            PointerPoint pointerPoint = args.GetCurrentPoint(this);

            // If ID is in dictionary, render graphic
            if (pointerDictionary.ContainsKey(id))
            {
                // Previous position and pressure
                PointerInfo pointerInfo = pointerDictionary[id];

                // Get new position and pressure
                Point point = pointerPoint.Position;
                double radius = appSettings.Thickness * pointerPoint.Properties.Pressure;

                // Render and flag that it's modified
                appSettings.IsImageModified = 
                    RenderOnBitmap(pointerInfo.PreviousPoint, pointerInfo.PreviousRadius, 
                                   point, radius, 
                                   appSettings.Color);

                // Update PointerInfo and store back in dictionary
                pointerInfo.PreviousPoint = point;
                pointerInfo.PreviousRadius = radius;
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

        bool RenderOnBitmap(Point point1, double radius1, Point point2, double radius2, Color color)
        {
            bool bitmapNeedsUpdate = false;

            // Define a line between the two points with rounded caps
            IGeometrySegment geoseg = null;

            // Adjust the points for any bitmap scaling
            Point center1 = ScaleToBitmap(point1);
            Point center2 = ScaleToBitmap(point2);

            // Find the distance between them
            double distance = Math.Sqrt(Math.Pow(center2.X - center1.X, 2) +
                                        Math.Pow(center2.Y - center1.Y, 2));

            // Choose the proper way to render the segment
            if (radius1 == radius2)
                geoseg = new RoundCappedLine(center1, center2, radius1);

            else if (radius1 < radius2 && radius1 + distance < radius2)
                geoseg = new RoundCappedLine(center1, center2, radius2);

            else if (radius2 < radius1 && radius2 + distance < radius1)
                geoseg = new RoundCappedLine(center1, center2, radius1);

            else if (radius1 < radius2)
                geoseg = new RoundCappedPath(center1, center2, radius1, radius2);

            else
                geoseg = new RoundCappedPath(center2, center1, radius2, radius1);

            // Find the minimum and maximum vertical coordinates
            int yMin = (int)Math.Min(center1.Y - radius1, center2.Y - radius2);
            int yMax = (int)Math.Max(center1.Y + radius1, center2.Y + radius2);

            yMin = Math.Max(0, Math.Min(bitmap.PixelHeight, yMin));
            yMax = Math.Max(0, Math.Min(bitmap.PixelHeight, yMax));

            // Loop through all the y coordinates that contain part of the segment
            for (int y = yMin; y < yMax; y++)
            {
                // Get the range of x coordinates in the segment
                xCollection.Clear();
                geoseg.GetAllX(y, xCollection);

                if (xCollection.Count == 2)
                {
                    // Find the minimum and maximum horizontal coordinates
                    int xMin = (int)(Math.Min(xCollection[0], xCollection[1]) + 0.5f);
                    int xMax = (int)(Math.Max(xCollection[0], xCollection[1]) + 0.5f);

                    xMin = Math.Max(0, Math.Min(bitmap.PixelWidth, xMin));
                    xMax = Math.Max(0, Math.Min(bitmap.PixelWidth, xMax));

                    // Loop through the X values
                    for (int x = xMin; x < xMax; x++)
                    {
                        {
                            // Set the pixel
                            int index = 4 * (y * bitmap.PixelWidth + x);
                            pixels[index + 0] = color.B;
                            pixels[index + 1] = color.G;
                            pixels[index + 2] = color.R;
                            pixels[index + 3] = 255;

                            bitmapNeedsUpdate = true;
                        }
                    }
                }
            }
            // Update bitmap
            if (bitmapNeedsUpdate)
            {
                // Find the starting index and number of pixels
                int start = 4 * yMin * bitmap.PixelWidth;
                int count = 4 * (yMax - yMin) * bitmap.PixelWidth;

                pixelStream.Seek(start, SeekOrigin.Begin);
                pixelStream.Write(pixels, start, count);
                bitmap.Invalidate();
            }

            return bitmapNeedsUpdate;
        }

        Point ScaleToBitmap(Point pt)
        {
            return new Point((pt.X - imageOffset.X) / imageScale,
                             (pt.Y - imageOffset.Y) / imageScale);
        }
    }
}
