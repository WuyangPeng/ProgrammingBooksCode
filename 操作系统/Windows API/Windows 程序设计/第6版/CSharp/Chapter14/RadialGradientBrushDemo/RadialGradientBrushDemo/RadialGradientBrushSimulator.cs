using System;
using System.IO;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.UI;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Media.Imaging;

namespace RadialGradientBrushDemo
{
    public class RadialGradientBrushSimulator : FrameworkElement
    {
        WriteableBitmap bitmap;
        byte[] pixels;
        Stream pixelStream;

        static readonly DependencyProperty gradientOriginProperty =
                DependencyProperty.Register("GradientOrigin",
                        typeof(Point),
                        typeof(RadialGradientBrushSimulator),
                        new PropertyMetadata(new Point(0.5, 0.5), OnPropertyChanged));

        static readonly DependencyProperty innerColorProperty =
                DependencyProperty.Register("InnerColor",
                        typeof(Color),
                        typeof(RadialGradientBrushSimulator),
                        new PropertyMetadata(Colors.White, OnPropertyChanged));

        static readonly DependencyProperty outerColorProperty =
                DependencyProperty.Register("OuterColor",
                        typeof(Color),
                        typeof(RadialGradientBrushSimulator),
                        new PropertyMetadata(Colors.Black, OnPropertyChanged));

        static readonly DependencyProperty clipToEllipseProperty =
                DependencyProperty.Register("ClipToEllipse",
                        typeof(bool),
                        typeof(RadialGradientBrushSimulator),
                        new PropertyMetadata(false, OnPropertyChanged));

        public static DependencyProperty imageSourceProperty =
                DependencyProperty.Register("ImageSource",
                        typeof(ImageSource),
                        typeof(RadialGradientBrushSimulator),
                        new PropertyMetadata(null));

        public RadialGradientBrushSimulator()
        {
            SizeChanged += OnSizeChanged;
        }

        public static DependencyProperty GradientOriginProperty
        {
            get { return gradientOriginProperty; }
        }

        public static DependencyProperty InnerColorProperty
        {
            get { return innerColorProperty; }
        }

        public static DependencyProperty OuterColorProperty 
        { 
            get { return outerColorProperty; }
        }

        public static DependencyProperty ClipToEllipseProperty
        {
            get { return clipToEllipseProperty; }
        }

        public static DependencyProperty ImageSourceProperty
        {
            get { return imageSourceProperty; }
        }

        public Point GradientOrigin
        {
            set { SetValue(GradientOriginProperty, value); }
            get { return (Point)GetValue(GradientOriginProperty); }
        }

        public Color InnerColor
        {
            set { SetValue(InnerColorProperty, value); }
            get { return (Color)GetValue(InnerColorProperty); }
        }
        public Color OuterColor
        {
            set { SetValue(OuterColorProperty, value); }
            get { return (Color)GetValue(OuterColorProperty); }
        }
        public bool ClipToEllipse
        {
            set { SetValue(ClipToEllipseProperty, value); }
            get { return (bool)GetValue(ClipToEllipseProperty); }
        }

        public ImageSource ImageSource
        {
            private set { SetValue(ImageSourceProperty, value); }
            get { return (ImageSource)GetValue(ImageSourceProperty); }
        }

        void OnSizeChanged(object sender, SizeChangedEventArgs args)
        {
            this.RefreshBitmap();
        }

        static void OnPropertyChanged(DependencyObject obj, DependencyPropertyChangedEventArgs args)
        {
            (obj as RadialGradientBrushSimulator).RefreshBitmap();
        }

        void RefreshBitmap()
        {
            if (this.ActualWidth == 0 || this.ActualHeight == 0)
            {
                this.ImageSource = null;
                bitmap = null;
                pixels = null;
                pixelStream = null;
                return;
            }

            if (bitmap == null || (int)this.ActualWidth != bitmap.PixelWidth ||
                                  (int)this.ActualHeight != bitmap.PixelHeight)
            {
                bitmap = new WriteableBitmap((int)this.ActualWidth, (int)this.ActualHeight);
                this.ImageSource = bitmap;
                pixels = new byte[4 * bitmap.PixelWidth * bitmap.PixelHeight];
                pixelStream = bitmap.PixelBuffer.AsStream();
            }
            else
            {
                for (int i = 0; i < pixels.Length; i++)
                    pixels[i] = 0;
            }

            double xOrigin = 2 * this.GradientOrigin.X - 1;
            double yOrigin = 2 * this.GradientOrigin.Y - 1;

            byte aOutsideCircle = 0;
            byte rOutsideCircle = 0;
            byte gOutsideCircle = 0;
            byte bOutsideCircle = 0;

            if (!this.ClipToEllipse)
            {
                double opacity = this.OuterColor.A / 255.0;
                aOutsideCircle = this.OuterColor.A;
                rOutsideCircle = (byte)(opacity * this.OuterColor.R);
                gOutsideCircle = (byte)(opacity * this.OuterColor.G);
                gOutsideCircle = (byte)(opacity * this.OuterColor.B);
            }

            int index = 0;

            for (int yPixel = 0; yPixel < bitmap.PixelHeight; yPixel++)
            {
                // Calculate y relative to unit circle
                double y = 2.0 * yPixel / bitmap.PixelHeight - 1;

                for (int xPixel = 0; xPixel < bitmap.PixelWidth; xPixel++)
                {
                    // Calculate x relative to unit circle
                    double x = 2.0 * xPixel / bitmap.PixelWidth - 1;

                    // Check if point is within circle
                    if (x * x + y * y <= 1)
                    {
                        // relative length from gradient origin to point
                        double length1 = 0;

                        // relative length from point to unit circle
                        //  (length1 + length2 = 1)
                        double length2 = 0;

                        if (x == xOrigin && y == yOrigin)
                        {
                            length2 = 1;
                        }
                        else
                        {
                            // Remember: xCircle^2 + yCircle^2 = 1
                            double xCircle = 0, yCircle = 0;

                            if (x == xOrigin)
                            {
                                xCircle = x;
                                yCircle = (y < yOrigin ? -1 : 1) * Math.Sqrt(1 - x * x);
                            }
                            else if (y == yOrigin)
                            {
                                xCircle = (x < xOrigin ? -1 : 1) * Math.Sqrt(1 - y * y);
                                yCircle = y;
                            }
                            else
                            {
                                // Express line from origin to point as y = mx + k
                                double m = (yOrigin - y) / (xOrigin - x);
                                double k = y - m * x;

                                // Now substitute (mx + k) for y into x^2 + y^2 = 1
                                // x^2 + (mx + k)^2 = 1
                                // x^2 + (mx)^2 + 2mxk + k^2 - 1 = 0
                                // (1 + m^2)x^2 + (2mk)x + (k^2 - 1) = 0 is quadratic equation
                                double a = 1 + m * m;
                                double b = 2 * m * k;
                                double c = k * k - 1;

                                // Now solve for x
                                double sqrtTerm = Math.Sqrt(b * b - 4 * a * c);
                                double x1 = (-b + sqrtTerm) / (2 * a);
                                double x2 = (-b - sqrtTerm) / (2 * a);

                                if (x < xOrigin)
                                    xCircle = Math.Min(x1, x2);
                                else
                                    xCircle = Math.Max(x1, x2);

                                yCircle = m * xCircle + k;
                            }

                            // Length from origin to point
                            length1 = Math.Sqrt(Math.Pow(x - xOrigin, 2) + Math.Pow(y - yOrigin, 2));

                            // Length from point to circle
                            length2 = Math.Sqrt(Math.Pow(x - xCircle, 2) + Math.Pow(y - yCircle, 2));

                            // Normalize those lengths
                            double total = length1 + length2;
                            length1 /= total;
                            length2 /= total;
                        }

                        // Interpolate color
                        double alpha = length2 * this.InnerColor.A + length1 * this.OuterColor.A;
                        double red= alpha * (length2 * this.InnerColor.R + 
                                             length1 * this.OuterColor.R) / 255;
                        double green = alpha * (length2 * this.InnerColor.G + 
                                                length1 * this.OuterColor.G) / 255;
                        double blue = alpha * (length2 * this.InnerColor.B + 
                                               length1 * this.OuterColor.B) / 255;

                        // Store in array
                        pixels[index++] = (byte)blue;
                        pixels[index++] = (byte)green;
                        pixels[index++] = (byte)red;
                        pixels[index++] = (byte)alpha;
                    }
                    else
                    {
                        pixels[index++] = bOutsideCircle;
                        pixels[index++] = gOutsideCircle;
                        pixels[index++] = rOutsideCircle;
                        pixels[index++] = aOutsideCircle;
                    }
                }
            }
            pixelStream.Seek(0, SeekOrigin.Begin);
            pixelStream.Write(pixels, 0, pixels.Length);
            bitmap.Invalidate();
        }
    }
}
