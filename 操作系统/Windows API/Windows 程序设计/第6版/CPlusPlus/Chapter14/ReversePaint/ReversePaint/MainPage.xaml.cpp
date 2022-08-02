//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"                // includes robuffer.h
#include "MainPage.xaml.h"

using namespace ReversePaint;

using namespace Microsoft::WRL;
using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Storage::Streams;
using namespace Windows::UI;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Media::Imaging;
using namespace Windows::UI::Xaml::Navigation;

using namespace PetzoldWindows8VectorDrawing;

MainPage::MainPage()
{
    InitializeComponent();

    pointerDictionary = ref new Map<unsigned int, Point>();

    roundCappedLine = ref new RoundCappedLine();
    xCollection = ref new Vector<float>();

    SizeChanged += ref new SizeChangedEventHandler(this, &MainPage::OnMainPageSizeChanged);
    Loaded += ref new RoutedEventHandler(this, &MainPage::OnMainPageLoaded);
}

void MainPage::OnMainPageSizeChanged(Object^ sender, SizeChangedEventArgs^ args)
{
    if (bitmap != nullptr)
        CalculateImageScaleAndOffset();
}

void MainPage::OnMainPageLoaded(Object^ sender, RoutedEventArgs^ args)
{
    // Create bitmap and get pixel buffer
    bitmap = ref new WriteableBitmap(320, 400);
    IBuffer^ buffer = bitmap->PixelBuffer;

    // Obtain IBufferByteAccess
    ComPtr<IBufferByteAccess> pBufferByteAccess;
    ComPtr<IUnknown> pBuffer((IUnknown*)buffer);
    pBuffer.As(&pBufferByteAccess);

    // Get pointer to pixel bytes
    pBufferByteAccess->Buffer(&pixels);

    // Initialize pixels to white
    int bitmapSize = 4 * bitmap->PixelWidth * bitmap->PixelHeight;

    for (int index = 0; index < bitmapSize; index++)
        pixels[index] = 0xFF;

    // Invalidate the WriteableBitmap
    bitmap->Invalidate();

    // Set to Image element
    whiteImage->Source = bitmap;
    CalculateImageScaleAndOffset();
}

void MainPage::CalculateImageScaleAndOffset()
{
    imageScale = (float)min(this->ActualWidth / bitmap->PixelWidth,
                            this->ActualHeight / bitmap->PixelHeight);

    imageOffset = Point(float(this->ActualWidth - imageScale * bitmap->PixelWidth) / 2,
                        float(this->ActualHeight - imageScale * bitmap->PixelHeight) / 2);
}

void MainPage::OnPointerPressed(PointerRoutedEventArgs^ args)
{
    unsigned int id = args->Pointer->PointerId;
    Point point = args->GetCurrentPoint(this)->Position;
    pointerDictionary->Insert(id, point);
    CapturePointer(args->Pointer);
}

void MainPage::OnPointerMoved(PointerRoutedEventArgs^ args)
{
    unsigned int id = args->Pointer->PointerId;

    if (pointerDictionary->HasKey(id))
    {
        Point point = args->GetCurrentPoint(this)->Position;
        Point previousPoint = pointerDictionary->Lookup(id);

        // Render the line
        RenderOnBitmap(previousPoint, point, 12, ColorHelper::FromArgb(0, 0, 0, 0));

        pointerDictionary->Insert(id, point);
    }
}

void MainPage::OnPointerReleased(PointerRoutedEventArgs^ args)
{
    unsigned int id = args->Pointer->PointerId;

    if (pointerDictionary->HasKey(id))
        pointerDictionary->Remove(id);
}

void MainPage::OnPointerCaptureLost(PointerRoutedEventArgs^ args)
{
    unsigned int id = args->Pointer->PointerId;

    if (pointerDictionary->HasKey(id))
        pointerDictionary->Remove(id);
}

void MainPage::RenderOnBitmap(Point point1, Point point2, float radius, Color color)
{
    bool bitmapNeedsUpdate = false;

    // Adjust the points for any bitmap scaling
    Point center1 = ScaleToBitmap(point1);
    Point center2 = ScaleToBitmap(point2);

    // Set object to render the line
    roundCappedLine->Set(center1, center2, radius);

    // Find the minimum and maximum vertical coordinates
    int yMin = (int)min(center1.Y - radius, center2.Y - radius);
    int yMax = (int)max(center1.Y + radius, center2.Y + radius);

    yMin = max(0, min(bitmap->PixelHeight, yMin));
    yMax = max(0, min(bitmap->PixelHeight, yMax));

    // Loop through all the y coordinates that contain part of the segment
    for (int y = yMin; y < yMax; y++)
    {
        // Get the range of x coordinates in the segment
        xCollection->Clear();
        roundCappedLine->GetAllX(float(y), xCollection);

        if (xCollection->Size == 2)
        {
            // Find the minimum and maximum horizontal coordinates
            int xMin = (int)(min(xCollection->GetAt(0), xCollection->GetAt(1)) + 0.5f);
            int xMax = (int)(max(xCollection->GetAt(0), xCollection->GetAt(1)) + 0.5f);

            xMin = max(0, min(bitmap->PixelWidth, xMin));
            xMax = max(0, min(bitmap->PixelWidth, xMax));

            // Loop through the X values
            for (int x = xMin; x < xMax; x++)
            {
                // Set the pixel
                int index = 4 * (y * bitmap->PixelWidth + x);
                pixels[index + 0] = color.B;
                pixels[index + 1] = color.G;
                pixels[index + 2] = color.R;
                pixels[index + 3] = color.A;
                bitmapNeedsUpdate = true;
            }
        }
    }

    // Update bitmap
    bitmap->Invalidate();
}

Point MainPage::ScaleToBitmap(Point pt)
{
    return Point((pt.X - imageOffset.X) / imageScale,
                 (pt.Y - imageOffset.Y) / imageScale);
}
