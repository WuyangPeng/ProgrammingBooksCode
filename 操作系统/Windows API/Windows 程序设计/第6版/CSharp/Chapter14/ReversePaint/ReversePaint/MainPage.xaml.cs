using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.UI;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media.Imaging;
using Petzold.Windows8.VectorDrawing;

namespace ReversePaint
{
    public sealed partial class MainPage : Page
    {
        Dictionary<uint, Point> pointerDictionary = new Dictionary<uint, Point>();
        List<double> xCollection = new List<double>();

        WriteableBitmap bitmap;
        byte[] pixels;
        Stream pixelStream;

        Point imageOffset = new Point();
        double imageScale = 1;

        public MainPage()
        {
            this.InitializeComponent();

            SizeChanged += OnMainPageSizeChanged;
            Loaded += OnMainPageLoaded;
        }

        void OnMainPageSizeChanged(object sender, SizeChangedEventArgs args)
        {
            if (bitmap != null)
                CalculateImageScaleAndOffset();
        }

        async void OnMainPageLoaded(object sender, RoutedEventArgs args)
        {
            bitmap = new WriteableBitmap(320, 400);
            pixels = new byte[4 * bitmap.PixelWidth * bitmap.PixelHeight];

            // Initialize pixels to white
            for (int index = 0; index < pixels.Length; index++)
                pixels[index] = 0xFF;

            pixelStream = bitmap.PixelBuffer.AsStream();
            await pixelStream.WriteAsync(pixels, 0, pixels.Length);
            bitmap.Invalidate();

            // Set to Image element
            whiteImage.Source = bitmap;
            CalculateImageScaleAndOffset();
        }

        void CalculateImageScaleAndOffset()
        {
            imageScale = Math.Min(this.ActualWidth / bitmap.PixelWidth,
                                  this.ActualHeight / bitmap.PixelHeight);
            imageOffset = new Point((this.ActualWidth - imageScale * bitmap.PixelWidth) / 2,
                                    (this.ActualHeight - imageScale * bitmap.PixelHeight) / 2);
        }

        protected override void OnPointerPressed(PointerRoutedEventArgs args)
        {
            uint id = args.Pointer.PointerId;
            Point point = args.GetCurrentPoint(this).Position;
            pointerDictionary.Add(id, point);
            CapturePointer(args.Pointer);
            base.OnPointerPressed(args);
        }

        protected override void OnPointerMoved(PointerRoutedEventArgs args)
        {
            uint id = args.Pointer.PointerId;
            Point point = args.GetCurrentPoint(this).Position;

            if (pointerDictionary.ContainsKey(id))
            {
                Point previousPoint = pointerDictionary[id];

                // Render the line
                RenderOnBitmap(previousPoint, point, 12, new Color());

                pointerDictionary[id] = point;
            }
            base.OnPointerMoved(args);
        }

        protected override void OnPointerReleased(PointerRoutedEventArgs args)
        {
            uint id = args.Pointer.PointerId;

            if (pointerDictionary.ContainsKey(id))
                pointerDictionary.Remove(id);

            base.OnPointerReleased(args);
        }

        protected override void OnPointerCaptureLost(PointerRoutedEventArgs args)
        {
            uint id = args.Pointer.PointerId;

            if (pointerDictionary.ContainsKey(id))
                pointerDictionary.Remove(id);

            base.OnPointerCaptureLost(args);
        }

        void RenderOnBitmap(Point point1, Point point2, double radius, Color color)
        {
            bool bitmapNeedsUpdate = false;

            // Adjust the points for any bitmap scaling
            Point center1 = ScaleToBitmap(point1);
            Point center2 = ScaleToBitmap(point2);

            // Create object to render the line
            RoundCappedLine line = new RoundCappedLine(center1, center2, radius);

            // Find the minimum and maximum vertical coordinates
            int yMin = (int)Math.Min(center1.Y - radius, center2.Y - radius);
            int yMax = (int)Math.Max(center1.Y + radius, center2.Y + radius);

            yMin = Math.Max(0, Math.Min(bitmap.PixelHeight, yMin));
            yMax = Math.Max(0, Math.Min(bitmap.PixelHeight, yMax));

            // Loop through all the y coordinates that contain part of the segment
            for (int y = yMin; y < yMax; y++)
            {
                // Get the range of x coordinates in the segment
                xCollection.Clear();
                line.GetAllX(y, xCollection);

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
                            pixels[index + 3] = color.A;
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
        }

        Point ScaleToBitmap(Point pt)
        {
            return new Point((pt.X - imageOffset.X) / imageScale,
                             (pt.Y - imageOffset.Y) / imageScale);
        }
    }
}
