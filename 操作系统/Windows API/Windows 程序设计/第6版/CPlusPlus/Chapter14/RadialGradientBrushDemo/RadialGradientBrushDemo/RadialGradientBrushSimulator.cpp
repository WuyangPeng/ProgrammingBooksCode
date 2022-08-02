#include "pch.h"    // includes wrl.h and robuffer.h
#include "RadialGradientBrushSimulator.h"

using namespace RadialGradientBrushDemo;

using namespace Microsoft::WRL;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Storage::Streams;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Media::Imaging;

DependencyProperty^ RadialGradientBrushSimulator::gradientOriginProperty =
        DependencyProperty::Register("GradientOrigin", 
                                     TypeName(Point::typeid), 
                                     TypeName(RadialGradientBrushSimulator::typeid),
                                     ref new PropertyMetadata(Point(0.5, 0.5),
                                     ref new PropertyChangedCallback(OnPropertyChanged)));

DependencyProperty^ RadialGradientBrushSimulator::innerColorProperty =
        DependencyProperty::Register("InnerColor", 
                                     TypeName(Color::typeid), 
                                     TypeName(RadialGradientBrushSimulator::typeid),
                                     ref new PropertyMetadata(Colors::White,
                                     ref new PropertyChangedCallback(OnPropertyChanged)));

DependencyProperty^ RadialGradientBrushSimulator::outerColorProperty =
        DependencyProperty::Register("OuterColor", 
                                     TypeName(Color::typeid), 
                                     TypeName(RadialGradientBrushSimulator::typeid),
                                     ref new PropertyMetadata(Colors::Black,
                                     ref new PropertyChangedCallback(OnPropertyChanged)));

DependencyProperty^ RadialGradientBrushSimulator::clipToEllipseProperty =
        DependencyProperty::Register("ClipToEllipse", 
                                     TypeName(bool::typeid), 
                                     TypeName(RadialGradientBrushSimulator::typeid),
                                     ref new PropertyMetadata(false,
                                     ref new PropertyChangedCallback(OnPropertyChanged)));

DependencyProperty^ RadialGradientBrushSimulator::imageSourceProperty =
        DependencyProperty::Register("ImageSource", 
                                     TypeName(ImageSource::typeid), 
                                     TypeName(RadialGradientBrushSimulator::typeid),
                                     ref new PropertyMetadata(nullptr));

RadialGradientBrushSimulator::RadialGradientBrushSimulator()
{
    SizeChanged += ref new SizeChangedEventHandler(this, &RadialGradientBrushSimulator::OnSizeChanged);
}

void RadialGradientBrushSimulator::OnSizeChanged(Object^ sender, SizeChangedEventArgs^ args)
{
    this->RefreshBitmap();
}

void RadialGradientBrushSimulator::OnPropertyChanged(DependencyObject^ sender, DependencyPropertyChangedEventArgs^ args)
{
    dynamic_cast<RadialGradientBrushSimulator^>(sender)->RefreshBitmap();
}

void RadialGradientBrushSimulator::RefreshBitmap()
{
    if (this->ActualWidth == 0 || this->ActualHeight == 0)
    {
        this->SetValue(ImageSourceProperty, nullptr);
        bitmap = nullptr;
        return;
    }

    if (bitmap == nullptr || (int)this->ActualWidth != bitmap->PixelWidth ||
                             (int)this->ActualHeight != bitmap->PixelHeight)
    {
        bitmap = ref new WriteableBitmap((int)this->ActualWidth, (int)this->ActualHeight);
        this->SetValue(ImageSourceProperty, bitmap);
    }

    // Get pixel buffer
    IBuffer^ buffer = bitmap->PixelBuffer;

    // Obtain IBufferByteAccess
    ComPtr<IBufferByteAccess> pBufferByteAccess;
    ComPtr<IUnknown> pBuffer((IUnknown*)buffer);
    pBuffer.As(&pBufferByteAccess);

    // Get pointer to pixel bytes
    byte* pixels;
    pBufferByteAccess->Buffer(&pixels);

    double xOrigin = 2 * this->GradientOrigin.X - 1;
    double yOrigin = 2 * this->GradientOrigin.Y - 1;

    byte aOutsideCircle = 0;
    byte rOutsideCircle = 0;
    byte gOutsideCircle = 0;
    byte bOutsideCircle = 0;

    if (!this->ClipToEllipse)
    {
        double opacity = this->OuterColor.A / 255.0;
        aOutsideCircle = this->OuterColor.A;
        rOutsideCircle = (byte)(opacity * this->OuterColor.R);
        gOutsideCircle = (byte)(opacity * this->OuterColor.G);
        bOutsideCircle = (byte)(opacity * this->OuterColor.B);
    }

    int index = 0;

    for (int yPixel = 0; yPixel < bitmap->PixelWidth; yPixel++)
    {
        // Calculate y relative to unit circle
        double y = 2.0 * yPixel / bitmap->PixelHeight - 1;

        for (int xPixel = 0; xPixel < bitmap->PixelWidth; xPixel++)
        {
            // Calculate x relative to unit circle
            double x = 2.0 * xPixel / bitmap->PixelWidth - 1;

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
                        yCircle = (y < yOrigin ? -1 : 1) * std::sqrt(1 - x * x);
                    }
                    else if (y == yOrigin)
                    {
                        xCircle = (x < xOrigin ? -1 : 1) * std::sqrt(1 - y * y);
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
                        double sqrtTerm = std::sqrt(b * b - 4 * a * c);
                        double x1 = (-b + sqrtTerm) / (2 * a);
                        double x2 = (-b - sqrtTerm) / (2 * a);

                        if (x < xOrigin)
                            xCircle = min(x1, x2);
                        else
                            xCircle = max(x1, x2);

                        yCircle = m * xCircle + k;
                    }

                    // Length from origin to point
                    length1 = sqrt(pow(x - xOrigin, 2) + pow(y - yOrigin, 2));

                    // Length from point to circle
                    length2 = sqrt(pow(x - xCircle, 2) + pow(y - yCircle, 2));

                    // Normalize those lengths
                    double total = length1 + length2;
                    length1 /= total;
                    length2 /= total;
                }

                // Interpolate color
                double alpha = length2 * this->InnerColor.A + length1 * this->OuterColor.A;
                double red= alpha * (length2 * this->InnerColor.R + 
                                     length1 * this->OuterColor.R) / 255;
                double green = alpha * (length2 * this->InnerColor.G + 
                                        length1 * this->OuterColor.G) / 255;
                double blue = alpha * (length2 * this->InnerColor.B + 
                                       length1 * this->OuterColor.B) / 255;

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

    // Invalidate the WriteableBitmap
    bitmap->Invalidate();
}
